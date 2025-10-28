import random
fit_chromosomes = []
def mutation(population):
    mutated_chromosomes = []
    #change one bit of each chromosomes
    for chromosome in population:
        mutated_bit = random.randint(1, 9)
        chromosome[mutated_bit] = random.randit(1, 9)
        mutated_chromosomes.append(chromosome)
    return mutated_chromosomes
def crossover(population):
    #choose parents:
    random.shuffle(population)
    parent_1 = population[:2]
    parent_2 = population[2:]
    children = []
    for i in range (len(parent_1)):
        #set a crossover index to cut on that index:
        crossover_idx = random.randint(0 ,5)
        #build all individuals:
        individuals = []
        individuals.append(parent_1[i][:crossover_idx])  
        individuals.append(parent_1[i][crossover_idx:])
        individuals.append(parent_2[i][:crossover_idx])
        individuals.append(parent_2[i][crossover_idx:])
        #add crossovered chromosomes into children list:
        children.append(individuals[0] + individuals[3])   
        children.append(individuals[2] + individuals[1])  
    return children 
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
generations = 95
initial_pop_size = 6
population = []
for i in range (initial_pop_size):
    chromosome = []
    for j in range (6):
        chromosome.append(random.randint(1,9))
    population.append(chromosome)
for generation in range(generations):
    print('Generation:', generation+1)
    print('------------')
    #selection: 
    parents = selection(population, fit_chromosomes)
    #crossover:
    children = crossover(parents)
    #add children int   o population:
    population = parents + children
solution = fit_chromosomes
best_fit = 0
best_chromosome = solution[0]
for chromosome in solution:
    if(fitness(chromosome) > best_fit):
        best_chromosome = chromosome
        best_fit = fitness(chromosome)
print(best_chromosome)
print(best_fit)