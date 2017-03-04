require 'data_file'

module ActorClass
  def self.export(id_pool, src_root, dst_root)
    src_dir = src_root + "/actor_class"
    dst_file = dst_root + "/actor_class"

    files = []
    Dir[src_dir + "/*"].sort.each do |f|
      files << DataFile.parse(f)
    end

    File.open(dst_file, "wb") do |dst|
      dst.write([files.size].pack("Q<"))
      files.each do |df|
        dst.write([df["Symbol"].ord].pack("L<"))
      end
    end
  end
end
