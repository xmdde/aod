using JuMP, GLPK
import JSON

data = JSON.parse(""" 
{
    "machines": {
        "m1": {"cost": 2},
        "m2": {"cost": 2},
        "m3": {"cost": 3}
    },
    "products": {
        "p1": {"max": 400, "price": 9, "cost": 4},
        "p2": {"max": 100, "price": 7, "cost": 1},
        "p3": {"max": 150, "price": 6, "cost": 1},
        "p4": {"max": 500, "price": 5, "cost": 1}
    },
    "production": {
        "m1, p1": 5,
        "m1, p2": 3,
        "m1, p3": 4,
        "m1, p4": 4,
        "m2, p1": 10,
        "m2, p2": 6,
        "m2, p3": 5,
        "m2, p4": 2,
        "m3, p1": 6,
        "m3, p2": 4,
        "m3, p3": 3,
        "m3, p4": 1
    }
}
""")
M = keys(data["machines"])
P = keys(data["products"])
gettime(m::String, p::String) = data["production"]["$(m), $(p)"]

model = Model(GLPK.Optimizer)
# processing time of products on given machines (in minutes)
@variable(model, x[M, P] >= 0, Int)

# machines cannot work more than 60h
@constraint(model, [m in M], sum(x[m, :]) <= 3600)

# there cannot be more products than demand
for p in P 
    @constraint(model, sum(x[m, p]/(gettime(m, p)) for m in M) <= data["products"][p]["max"])   
end

@objective(model, Max, sum((x[m, p]/(gettime(m, p)) * (data["products"][p]["price"] - data["products"][p]["cost"]) - ((x[m, p]/60) * data["machines"][m]["cost"])) for m in M, p in P))
optimize!(model)

println("profit = ", objective_value(model))
println("kg of products made:")
for p in P 
    println(p,  " => ", value.(sum(x[m, p] * (gettime(m, p)^-1) for m in M))) 
end
println("schedule:")
for m in M, p in P
    if  !(value(x[m, p]) ≈ 0)    
        println(m, " => ", p, ": ", value(x[m, p]))
    end
end

@show termination_status(model)
@show value.(x)