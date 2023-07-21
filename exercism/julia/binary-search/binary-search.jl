function binarysearch(list, key; by=nothing, rev=nothing, lt=nothing)
    count = 1
    indexes = collect(1:length(list))
    if by !== nothing
        list = by.(list)
        key = by(key)
    end
    while ~isempty(list)
        n = length(list)
        k = trunc(Int, n // 2) + 1
        if key != list[k]
            popat!(list, k)
            popat!(indexes, k)
            count += 1
        else
            return indexes[k]:indexes[k]
        end
    end
    return count:0
end