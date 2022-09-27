function to_rna(dna)
    dna_rna_mapping = Dict('G' => 'C', 'C' => 'G',
                'T' => 'A', 'A' => 'U')
    rna = ""
    for k in dna
        try
            rna *= dna_rna_mapping[k]
        catch
            throw(ErrorException("Invalid input"))
        end
    end
    return rna
end

