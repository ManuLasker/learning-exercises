"""
    count_nucleotides(strand)

The frequency of each nucleotide within `strand` as a dictionary.

Invalid strands raise a `DomainError`.

"""
function count_nucleotides(strand)
    dict = Dict('A' => 0, 'C' => 0, 'T' => 0, 'G' => 0)
    for s in strand
        try
            dict[s] += 1
        catch err
            throw(DomainError("Error"))
        end
    end
    return dict
end
