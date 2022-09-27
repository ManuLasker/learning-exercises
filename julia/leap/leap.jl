"""
    is_leap_year(year)

Return `true` if `year` is a leap year in the gregorian calendar.

"""
function is_leap_year(year)
    is_leap = false
    if year%4 == 0
        if year%100 == 0 && year%400 != 0
            is_leap = false
        else
            is_leap = true
        end
    end
    return is_leap
end

