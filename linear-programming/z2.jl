using JuMP, GLPK
function parsedata() 
    open("graph.txt") do f
        n = parse(Int, readline(f)) #number of cities
        a = parse(Int, readline(f)) #number of edges in the graph
        graph = falses(n,n)
        cost = zeros(Int64, n, n)
        time = zeros(Int64, n, n)
        #cost and time
    for it in 1:a
        i, j, c, t = [parse(Int, x) for x in split(readline(f), " ")] #remember to change data in the file
        graph[i, j] = true
        cost[i, j] = c
        time[i, j] = t
    end
    start = parse(Int, readline(f)) 
    finish = parse(Int, readline(f)) 
    T = parse(Int, readline(f)) 
    return n, a, graph, cost, time, start, finish, T
    end
end

f = parsedata()
n = f[1]
a = f[2]
graph = f[3]
cost = f[4]
time = f[5]
start = f[6]
finish = f[7]
T = f[8]

model = Model(GLPK.Optimizer)
@variable(model, 0 <= path[i=1:n, j=1:n] <= 1, Int)

# we cannot use nonexistent edges in path
@constraint(model, [i in 1:n, j in 1:n; graph[i,j] == 0], path[i, j] == 0)

# source
@constraint(model, sum(path[start, :]) - sum(path[:, start]) == 1)

# destination
@constraint(model, sum(path[finish, :]) - sum(path[:, finish]) == -1)

# for every other node sum of incoming edges should be equal to outcoming
@constraint(model, [i = 1:n; i != start && i != finish], sum(path[i, :]) == sum(path[:, i]))

@constraint(model, sum(path[i,j] for i in 1:n, j in 1:n) <= T)

@objective(model, Min, sum(path[i,j]*cost[i,j] for i in 1:n, j in 1:n))

optimize!(model)
@show termination_status(model)
@show value.(path)