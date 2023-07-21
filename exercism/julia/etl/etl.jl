function transform(input::AbstractDict)
    return reduce(merge, [Dict((lowercase(value) => key) for value in values) for (key, values) in pairs(input)])
end

