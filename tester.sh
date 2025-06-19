# Example

./philo 1 200 200 200
./philo 2 800 200 200
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
./philo 4 310 200 200
./philo 4 500 200 1.2
./philo 4 0 200 200 
./philo 4 -500 200 200
./philo 4 500 200 2147483647 //
./philo 4 2147483647 200 200
./philo 4 214748364732 200 200
./philo 4 200 210 200 
./philo 5 800 200 150 

# Expected Result

# Philosopher 1 takes a fork and dies after 200 ms.
# No philosopher dies.
# No philosopher dies.
# The program stops when each philosopher has eaten 7 times.
# No philosopher dies.
# A philosopher dies.
# Invalid argument.
# Invalid argument.
# Invalid argument.
# A philosopher dies after 500 ms
# No philosopher dies.
# Invalid argument.
# A philosopher dies, it should display the death before 210 ms.
# No philosopher dies.
