-- FILE_NAME = "test_data.txt"
FILE_NAME = "data.txt"

local function file_exists()
    local f = io.open(FILE_NAME, "r")
    if f then f:close() end
    return f ~= nil
end

local function main_part_1()
    if not file_exists() then return 0 end

    local file = io.open(FILE_NAME, "r")
    local sum = 0
    local max = -1

    for line in file:lines("*l") do
        if line ~= "" then
            sum = sum + tonumber(line)
        else
            if max <= sum then
                max = sum
            end
            sum = 0
        end
    end

    return max
end

local function main_part_2()
    if not file_exists() then return 0 end

    local file = io.open(FILE_NAME, "r")
    local sum = 0
    local i = 1
    local top_3 = {}

    for line in file:lines("*l") do
        if line ~= "" then
            sum = sum + tonumber(line)
        else
            top_3[i] = sum
            if i == 4 then
                table.sort(top_3, function (a,b) return a>b end)
                i = 3
            end
            i = i + 1
            sum = 0
        end
    end

    local get_sum = function (...)
        local sum = 0
        for _, value in pairs({...}) do
            sum = sum + value
        end
        return sum
    end


    return get_sum(table.unpack(top_3, 1, 3))
end

print(string.format("part1: %i", main_part_1()))
print(string.format("part2: %i", main_part_2()))
