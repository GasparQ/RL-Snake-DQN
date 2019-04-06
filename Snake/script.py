import pySnake
import time

pySnake.make('monGrosSNAKE')
pySnake.reset()

done = False
while not done:
    time.sleep(0.5)
    obs, reward, done = pySnake.step(1)
    print(obs, reward, done)
    pass