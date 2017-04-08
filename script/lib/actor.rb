require 'data_file'

module Actor
  def self.export(id_pool, src_root, dst_root)
    src_dir = src_root + "/actor"
    dst_file = dst_root + "/actor"

    files = []
    Dir[src_dir + "/*"].sort.each do |f|
      files << DataFile.parse(f)
    end

    File.open(dst_file, "wb") do |dst|
      dst.write([files.size].pack("Q<"))
      files.each do |df|
        klass = df["Class"]
        klass_id = id_pool["ActorClass"][klass]
        difficulty = df["Difficulty"].to_i
        color = df["Color"].to_i
        dst.write([klass_id, difficulty, color].pack('CCC'))
      end
    end
  end
end
