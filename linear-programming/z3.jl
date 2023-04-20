using JuMP, GLPK

# mini[p,z] - minimum number of police cars for area p on shift z
mini = 
[2 4 3;
 3 6 5;
 5 7 6]
# maxi[p,z] - maximum number of police cars for area p on shift z
maxi = 
[3 7 5;
5 7 10;
8 12 10]
shiftsC = [10, 20, 18]
areasC = [10, 14, 13]

model = Model(GLPK.Optimizer)

# plan[p,z] - number of police cars assigned to area p on shift z
@variable(model, plan[1:3, 1:3] >= 0)

@objective(model, Min, sum(plan[i,j] for i in 1:3, j in 1:3))

# for each shift there should be enough cars according to shiftsC
for i in 1:3
    @constraint(model, sum(plan[p,i] for p in 1:3) >= shiftsC[i])
end
# there should be enough cars assigned to each area
for i in 1:3
    @constraint(model, sum(plan[i,z] for z in 1:3) >= areasC[i])
end

for p in 1:3, z in 1:3
    @constraint(model, mini[p,z] <= plan[p,z])
end

for p in 1:3, z in 1:3
    @constraint(model, plan[p,z] <= maxi[p,z])
end

optimize!(model)
@show termination_status(model)
@show value.(plan)