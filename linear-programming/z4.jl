using JuMP, GLPK

function parsedata() 
    open("containers.txt") do f
        m = parse(Int, readline(f))
        n = parse(Int, readline(f))
        k = parse(Int, readline(f))
        c = parse(Int, readline(f))
        container = falses(m,n)
    for it in 1:c
        i, j = [parse(Int, x) for x in split(readline(f), " ")]
        container[i, j] = true
    end
    return m, n, k, c, container
    end
end

f = parsedata()
m = f[1]
n = f[2]
k = f[3]
c = f[4]
container = f[5]

model = Model(GLPK.Optimizer)
@variable(model, 0 <= plan[i=1:m, j=1:n] <= 1, Int)

# cameras can't be on the same positions as containers
@constraint(model, [i in 1:m, j in 1:n; container[i,j]], plan[i, j] == 0)

# every container should be surrounded by min 1 camera
@constraint(model, [i in 1:m, j in 1:n; container[i,j]], sum(plan[i, x] for x in max(1, j-k):min(n, j+k)) + sum(plan[x, j] for x in max(1,i-k):min(m,i+k)) >= 1)

@objective(model, Min, sum(plan[i,j] for i in 1:m, j in 1:n))
optimize!(model)
@show termination_status(model)
@show value.(plan)