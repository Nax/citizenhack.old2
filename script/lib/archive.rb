class Archive
  class Member
    attr_reader :name, :path

    def initialize(name, path)
      @name = name
      @path = path
    end

    def size
      File.size(@path)
    end

    def read
      File.read(@path)
    end
  end

  def initialize(filename)
    @file = File.open(filename, "wb")
    @members = []
  end

  def add(name, path)
    @members << Member.new(name, path)
  end

  def save
    @file.write([@members.size].pack("Q<"))
    offset = 0
    @members.each do |member|
      @file.write([offset, member.size, member.name.size, member.name].pack("Q<Q<Q<a*"))
      offset += member.size
    end
    @members.each do |member|
      @file.write(member.read)
    end
    @file.close
  end

  def self.open(filename, &block)
    archive = self.new(filename)
    yield archive
    archive.save
    nil
  end

  def self.create(filename, path)
    archive = self.new(filename)
    Dir.chdir(path) do
      files = Dir["**/*"].select{|f| File.file?(f)}
      files.each {|f| archive.add(f, f)}
      archive.save
    end
  end
end
