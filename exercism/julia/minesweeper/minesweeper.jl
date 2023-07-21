function is_possible(i, j, num_row, num_col)
    (num_row >= i > 0 && num_col >= j > 0) ? true : false
end

function count_asterisks(mines_matrix, i, j)
    # count asterisks
    row_size = length(mines_matrix)
    col_size = length(mines_matrix[1])
    # six search
    count = 0
    idx = [[0, -1], [-1, -1], [-1, 0],  [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1]]
    for (i_temp, j_temp) in idx
        if is_possible(i + i_temp, j + j_temp, row_size, col_size)
            s_val = mines_matrix[i + i_temp][j + j_temp]
            if s_val == "*"
                count += 1
            end
        end
    end
    return count
end

function annotate(mines_vector)
    copy_mines = map(x -> split(x, ""), mines_vector)
    # if position is an empty space:
    # get adjacents indexes
    # count number of * -> if 0 leave empty, if not put the number of *
    for (i, row) in enumerate(mines_vector)
        for (j, s) in enumerate(row)
            if s != '*'
                num_asterisks = count_asterisks(copy_mines, i, j)
                if num_asterisks != 0
                    copy_mines[i][j] = string(num_asterisks)
                end
            end
        end
    end
    return map(x -> join(x, ""), copy_mines)
end