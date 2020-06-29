# Natural Selection Simulator
Simple Natural Selection Simulator created with C++ with SDL2. Results visualization written in Python 3.8

Inspired by **Primer** YouTube channel



![Blobs1](https://user-images.githubusercontent.com/60292948/86057726-01ea9900-ba60-11ea-9cd6-83885a6ce7ab.png)

### Rules of the game :

1. Individuals wander across the board and look for the food. Their path is random.
2. Individual survives generation if it manages to find 1 piece of food. Eating 2 pieces of food guarantees reproduction in the next generation.
3. Individuals have 3 variable parameters; radius of sight, speed and size.
4. Individual eats other individual, when one's size is 1.25 times bigger than victim's.
5. When food shows up in the indidual's area of sight, individual goes straight for the food.
6. Similary, bigger individual chases smaller, while smaller run from the bigger.
7. Every individual has the same amount of energy at the beginning of each generation. Individuals bears the cost of every step according to following formula:

     *energy cost = sight + speed^2 + size^3*  
     
     
8. During reproducation phase, individuals will create offspring, whose parameters differs from parent's by random generated value with probability density according to normal distribution

![Distribution](https://miro.medium.com/max/24000/1*IdGgdrY_n_9_YfkaCh-dag.png)

After all the generation passed, Python script will sum-up population evolution with 3 graphs:

