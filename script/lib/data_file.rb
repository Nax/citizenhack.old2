class DataFile
  def initialize
    @data = {}
  end

  def read(filename)
    File.open(filename, "r") do |file|
      file.each_line do |line|
        line = line.strip
        next if line.empty? || line[0] == '#'
        key, value = *line.split('=', 2).map{|v| v.strip}
        @data[key] = value
      end
    end
  end

  def [](index)
    @data[index]
  end

  def self.parse(filename)
    df = self.new
    df.read(filename)
    df
  end
end
