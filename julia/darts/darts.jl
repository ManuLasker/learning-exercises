function is_inside(x, y, r)
    return  x^2 + y^2 <= r^2
end

function score(x, y)
    if is_inside(x, y, 1)
        return 10
    elseif is_inside(x, y, 5)
        return 5
    elseif is_inside(x, y, 10)
        return 1
    else
        return 0
    end
end