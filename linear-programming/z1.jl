using JuMP
using HiGHS

airports = 4
companies = 3
prices = 
[10 7 8;
10 11 14;
9 12 4;
11 13 9]

C = [275000, 550000, 660000]
A = [110000, 220000, 330000, 440000]

model = Model(HiGHS.Optimizer)

# plan[i,j] - amount of fuel bought from company j to airport i
@variable(model, plan[1:airports, 1:companies] >= 0)

for i in 1:airports
    @constraint(model, sum(plan[i, j] for j in 1:companies) == A[i])
end

for i in 1:companies
    @constraint(model, sum(plan[j, i] for j in 1:airports) <= C[i])
end

@objective(model, Min, sum(prices[i, j] * plan[i, j] for i in 1:airports, j in 1:companies))
optimize!(model)

for a in 1:airports, c in 1:companies
    if (value(plan[a,c]) != 0)
        println(c, " -> ", a, ": ", value(plan[a, c]))
    end
end

println(objective_value(model))