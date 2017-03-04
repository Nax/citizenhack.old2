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
end
