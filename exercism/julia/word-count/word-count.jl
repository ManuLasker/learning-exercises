function wordcount(sentence)
    sentence = lowercase(sentence)
    word_counts = Dict()
    for word_indexes in findall(r"\w+('\w+)?", sentence)
        word = sentence[word_indexes]
        haskey(word_counts, word) ? word_counts[word] += 1 : word_counts[word] = 1
    end
    return word_counts
end
