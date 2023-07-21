function detect_anagrams(subject, candidates)
    order(s) = join(sort!(collect(s)))
    anagrams = []
    for candidate in candidates
        if lowercase(candidate) != lowercase(subject) && order(lowercase(candidate)) == order(lowercase(subject))
            push!(anagrams, candidate)
        end
    end
    return anagrams
end
