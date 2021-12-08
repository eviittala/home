import pygame
import time
import random

pygame.init()

white = (255, 255, 255)
yellow = (225, 225, 102)
blue = (0, 0, 255)
red = (255, 0, 0)
green = (0, 255, 0)
black = (0, 0, 0)

display_width = 800
display_height = 600

display = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('Snake game by Eero')
font_style = pygame.font.SysFont("bahnschrift", 25)
score_font = pygame.font.SysFont("comicsansms", 35)
clock = pygame.time.Clock()

class Snake:
    def __init__(self):
        self.speed = 5
        self.blockSize = 10
        self.length = 1
        self.list = [[display_width / 2, display_height / 2]]
        self.isHit = False

    def addHead(self, newHead):
        self.list.insert(0, newHead)
        if len(self.list) > self.length:
            del self.list[-1]

    def draw(self):
        i = 1
        for x in self.list:
            if i % 2:
                pygame.draw.rect(display, blue, [x[0], x[1], self.blockSize, self.blockSize])
            else:
                pygame.draw.rect(display, yellow, [x[0], x[1], self.blockSize, self.blockSize])
            i += 1
    
    def getSpeed(self):
        return self.speed
    
    def increaseSpeed(self, inc = 1):
        self.speed += inc
    
    def addLength(self, size = 1):
        self.length += size
        self.increaseSpeed()

    def getLen(self):
        return self.length

    def getHead(self):
        return self.list[0]
        
    def move(self, eventKey):
        newHead = [self.getHead()[0], self.getHead()[1]]
        if eventKey == pygame.K_LEFT:
            newHead[0] -= self.blockSize
        elif eventKey == pygame.K_RIGHT:
            newHead[0] += self.blockSize
        elif eventKey == pygame.K_UP:
            newHead[1] -= self.blockSize
        elif eventKey == pygame.K_DOWN:
            newHead[1] += self.blockSize

        if not self.isOutOfBoundOrHit(newHead):
            self.addHead(newHead)
        else:
            self.isHit = True

    def isOutOfBoundOrHit(self, newHead):
        if newHead[0] >= display_width or newHead[0] < 0 or newHead[1] >= display_height or newHead[1] < 0:
            return True
        if len(self.list) > 1:
            for i in range(len(self.list)):
                if self.list[i][0] == newHead[0] and self.list[i][1] == newHead[1]:
                    return True
        return False        

class Food:
    def __init__(self):
        self.foodXY = [[random.randrange(0, display_width - 5), random.randrange(0, display_height - 5)]]
    
    def isHit(self, snakeXY):
        if snakeXY[0] >= (self.foodXY[0][0] - 10) and snakeXY[0] <= (self.foodXY[0][0] + 10) and snakeXY[1] >= (self.foodXY[0][1] - 10) and snakeXY[1] <= (self.foodXY[0][1] + 10):
            self.foodXY = [[random.randrange(0, display_width - 5), random.randrange(0, display_height - 5)]]
            return True
        return False
        
    def getFoodXY(self):
        return self.foodXY[0]

def message(message, color):
    msg = font_style.render(message, True, color)
    display.blit(msg, [display_width / 6, display_height / 3])

def endGame(snake):
    while True:
        message("You lost! Press Q or C to play again", red)
        your_score(snake.getLen() - 1)
        pygame.display.update()

        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    return True
                if event.key == pygame.K_c:
                    return False
            elif event.type == pygame.QUIT:
                return True

def your_score(score):
    value = score_font.render("Your Score: " + str(score), True, black)
    display.blit(value, [0, 0])

def gameLoop():
    continueGame = True
    eventKey = pygame.K_UP
    snake = Snake()
    food = Food()

    while continueGame:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                continueGame = False
            if event.type == pygame.KEYDOWN:
                eventKey = event.key

        snake.move(eventKey)
        display.fill(white)
        pygame.draw.rect(display, green, [food.getFoodXY()[0], food.getFoodXY()[1], 8, 8])
        snake.draw()

        pygame.display.update()
        if food.isHit(snake.getHead()):
            snake.addLength()

        if snake.isHit:
            if endGame(snake):
               break;
            else:
                gameLoop()

        clock.tick(snake.getSpeed())

    pygame.quit()
    quit()

gameLoop()

