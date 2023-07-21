using Unicode
const TEST_GRAPHEMES = true

function myreverse(str)
    return join(reverse(collect(graphemes(str))))
end