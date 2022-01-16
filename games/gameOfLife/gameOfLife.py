import sys, pygame, random, argparse
from pygame.locals import *
pygame.init()

frames_per_second = 60
black = 0, 0, 0
blue = 0, 0, 255
white = 255, 255, 255
clock = pygame.time.Clock()
cells = []

def getXY(pos):
    ret = []
    ret.append(int(pos % number_of_cells_x))
    ret.append(int(pos / number_of_cells_y))
    return ret

def getPos(x, y):
    return y * number_of_cells_y + x

class Cell:
    def __init__(self, alive):
        self.isAlive = alive
        self.nextStage = False

    def getNextStage(self):
        '''Updates isAlive and gets it '''
        self.isAlive = self.nextStage
        return self.isAlive

def checkCells():
    for pos in range(number_of_cells_x * number_of_cells_y):
        xy = getXY(pos)
        assert getPos(xy[0], xy[1]) == pos 
        cell = cells[pos]
        neighbours = 0
        for ix, iy in [[-1, 0], [-1, -1], [0, -1], [1, -1], [1, 0], [1, 1], [0, 1], [-1, 1]]:
            tx = xy[0] + ix
            ty = xy[1] + iy
            if 0 <= tx and tx < number_of_cells_x and 0 <= ty and ty < number_of_cells_y:
                tPos = getPos(tx, ty)
                if cells[tPos].isAlive:
                    neighbours = neighbours + 1

        if cell.isAlive:
            if neighbours == 2 or neighbours == 3:
                cell.nextStage = True
            else:
                cell.nextStage = False
        elif neighbours == 3:
             cell.nextStage = True
        else:
             cell.nextStage = False

def gameInit():
    global size
    global screen
    size = number_of_cells_x * (size_of_cell + 1), number_of_cells_y * (size_of_cell + 1)
    screen = pygame.display.set_mode(size)
    pygame.display.set_caption('Game of Life by Eero Viittala')

    for i in range(number_of_cells_x * number_of_cells_y):
        cells.append(Cell(False))

def randomCells():
    for pos in range(number_of_cells_x * number_of_cells_y):
        ran = random.randrange(2)
        if ran:
            cells[pos].nextStage = True
        else:
            cells[pos].nextStage = False
            

def gameLoop(run = False):
    while 1:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_s:
                    run = True
                if event.key == pygame.K_r:
                    randomCells()
                if event.key == pygame.K_t:
                    run = False
                if event.key == pygame.K_n:
                    checkCells()
                if event.key == pygame.K_c:
                    for pos in range(number_of_cells_x * number_of_cells_y):
                        cells[pos].nextStage = False
            if event.type == MOUSEBUTTONDOWN:
                mousePressed = pygame.mouse.get_pressed()
                for pos in range(number_of_cells_x * number_of_cells_y):
                    xy = getXY(pos)
                    xstart = (size_of_cell + 1) * xy[0]
                    ystart = (size_of_cell + 1) * xy[1]
                    if xstart <= event.pos[0] and event.pos[0] <= (xstart + size_of_cell) and ystart <= event.pos[1] and event.pos[1] <= (ystart + size_of_cell):
                        if cells[pos].nextStage:
                            cells[pos].nextStage = False
                        else:
                            cells[pos].nextStage = True
                    

        screen.fill(white)
        for pos in range(number_of_cells_x * number_of_cells_y):
            xy = getXY(pos)
            if cells[pos].getNextStage():
                pygame.draw.rect(screen, black, [(size_of_cell + 1)*xy[0], (size_of_cell + 1)*xy[1], size_of_cell, size_of_cell])

        pygame.display.flip()
        clock.tick(frames_per_second)
        if run:
            checkCells()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog = 'gameOfLife', 
                                    description = 'Change Game Of Life  parameters',
                                    formatter_class = argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument('-s', '--screen_size', type = int, default = 500, help='Set screen size in pixels') 
    parser.add_argument('-c', '--cell_size', type = int, default = 3, help='Set cell size in pixels') 
    parser.add_argument('-r', '--run', action='store_true',  help='Run game with randomized cells') 
    args = parser.parse_args()
    global number_of_cells_x
    global number_of_cells_y
    global size_of_cell
    number_of_cells_x = args.screen_size
    number_of_cells_y = args.screen_size
    size_of_cell = args.cell_size
    
    gameInit()
    if args.run:
        randomCells()
    gameLoop(args.run)
