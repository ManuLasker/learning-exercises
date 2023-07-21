function all_uppercase(val)
    # Clean regex pipeline
    re_patterns = [r"[^\w]",
                   r"[0-9]+"]
    for re in re_patterns
        val = replace(val, re => "")
    end
    if length(val) > 0
        return all(isuppercase(ch) for ch in val)
    end
    return false
end

function classify_stimulus(val)
    val = replace(val, r"[\s]" => "")
    if val == ""
        return :silence
    elseif endswith(val, '?') && (~all_uppercase(val))
        return :question
    elseif endswith(val, '?') && all_uppercase(val)
        return :forceful_question
    elseif all_uppercase(val)
        return :yelling
    else
        return :misc
    end
end

function bob(stimulus)
    # definde responses
    response = Dict(
        :question => "Sure.",
        :yelling => "Whoa, chill out!",
        :silence => "Fine. Be that way!",
        :misc => "Whatever.",
        :forceful_question => "Calm down, I know what I'm doing!",
    )
    pred = classify_stimulus(stimulus)
    return response[pred]
end
