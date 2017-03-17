class IdentifierPool
  class Category
    attr_reader :name

    def initialize(name)
      @name = name
      @data = {"None" => 0}
    end

    def <<(identifier)
      return if @data.include?(identifier)
      @data[identifier] = @data.size
      nil
    end

    def [](identifier)
      @data[identifier]
    end

    def identifiers
      @data.keys
    end

    def byte_size
      if @data.size <= (2 ** 8)
        1
      elsif @data.size <= (2 ** 16)
        2
      else
        4
      end
    end

    def serialize_header
      guard = @name[0].downcase + @name[1..-1]
      guard.gsub!(/[A-Z]/) {|m| '_' + m.downcase}
      guard.upcase!
      guard += '_ID_H'
      type = "uint#{byte_size * 8}_t"

      header = <<-EOF
#ifndef #{guard}
#define #{guard}

#include <cstdint>

enum class #{@name}ID : #{type}
{
#{@data.map{|k, v| "    %-15s = %d" % [k, v]}.join(",\n")}
};

constexpr const uint32_t #{@name}Count = #{@data.size};

#endif
      EOF
      header
    end
  end

  def initialize
    @categories = {}
  end

  def push(category, identifier)
    @categories[category] ||= Category.new(category)
    @categories[category] << identifier
    nil
  end

  def categories
    @categories.values
  end

  def generate_headers(path)
    Dir.chdir(path) do
      @categories.each do |name, value|
        filename = name[0].downcase + name[1..-1]
        filename.gsub!(/[A-Z]/){|m| '_' + m.downcase}
        filename += "_id.h"
        File.open(filename, "w") do |file|
          file.write(value.serialize_header)
        end
      end
    end
  end
end
