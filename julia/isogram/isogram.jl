function isisogram(s)
    s = replace(s, r"([^\w]|[0-9])" => "") # replace all non alphabet to empty space
    s = collect(join(split(lowercase(s)), ""))
    return length(s) == length(unique(s)) ? true : false
end
