import random
fit_payment = []
balance = int(input("Enter Total Balance: "))
cake_order_cost = 50
cake_cost_per_kilogeram = 250
candles_cost = 30
hat_cost = 60
balloons_cost = 40
reservation_cost = 300
gift_1_cost = int(input("Enter Gift Number 1's Cost: "))
def mutation(population):
    mutated_chromosomes = []
    #change one bit of each chromosomes
    for chromosome in population:
        mutated_bit = random.randint(1, 9)
        chromosome[mutated_bit] = random.randit(1, 9)
        mutated_chromosomes.append(chromosome)
    return mutated_chromosomes
def fitness(solution):
    return (100 - abs(30 - (solution[0] + 2*solution[1] - 3*solution[2] + solution[3] + 4*solution[4]+ solution[5])))
def selection(population , fit_chromosomes):
    fitnesses = []
    #get all fitnesses of chromosomes in population
    for chromosome in population:
        fitness_new = fitness(chromosome)
        fitnesses.append(fitness_new)
    #get total fitness of the whole population:
    total_fitness = sum(fitnesses)
    #sort chromosomes bt their fitnesses:
    fit_pop_map = list(zip(fitnesses, population))
    fit_pop_map.sort(reverse = True)
    #find the chromosomes which are good enough:
    for individual in fit_pop_map:
        if individual[0]>=94:
            if individual[1] not in fit_chromosomes:
                fit_chromosomes.append(individual[1])
    #choose 4 best chromosomes as selectyed population:
    fit_pop_map = fit_pop_map[:4]
    fit, pop = zip(*fit_pop_map)
    return list(pop)
calculations = 100
initial_pop_size = 7
population = []
for i in range (initial_pop_size):
    chromosome = []
    for j in range (6):
        chromosome.append(random.randint(1,9))
    population.append(chromosome)
for generation in range(calculations):
    print('Generation:', generation+1)
    print('------------')
    #selection: 
    parents = selection(population, fit_payment)
    #crossover:
    #add children into population:
    population = parents
final_result = fit_payment
best_chromosome = final_result[0]
for chromosome in final_result:
    if(fitness(chromosome) > balance):
        best_chromosome = chromosome
        balance = fitness(chromosome)
print(best_chromosome)
print(balance)