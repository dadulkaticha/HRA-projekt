import pygame
import random
from assets import *
from classes.snake import Snake

"""
    summary: trida pro ovoce
    x -> x pozice ovoce
    y -> y pozice ovoce
    img -> obrazek ovoce
    counter -> pocitadlo pro pohyb ovoce
    rand -> nahodne vybrany smer pohybu
    move -> promenna pro urceni jestli se ovoce hybe nebo ne
    rect -> obdelnik ovoce
"""
snake = Snake(head_sprite, ocas_sprite, PINK)
class Fruit():
    def __init__(self, img):

        #generuje ovoce na random pozice
        self.x = int(random.randint(0,WIDTH-BLOCK_SIZE)/BLOCK_SIZE)*BLOCK_SIZE
        self.y = int(random.randint(0,HEIGHT-BLOCK_SIZE)/BLOCK_SIZE)*BLOCK_SIZE
        self.img = img
        self.counter=0
        self.rand = random.choice([1, 2, 3, 4]) #pokud se ovoce hybe tak se vybere jedna ze 4 moznosti
        self.move = random.choice([True, False]) #generuje jestli se bude hybat nebo ne

        #pokud je ovoce na stejne pozici jako nejaka cast hada, vygeneruje se znova
        for rect in snake.body:
            while rect.x == self.x and rect.y == self.y or snake.head.x == self.x and snake.head.y == self.y:
                self.x = int(random.randint(0,WIDTH)/BLOCK_SIZE)*BLOCK_SIZE
                self.y = int(random.randint(0,HEIGHT)/BLOCK_SIZE)*BLOCK_SIZE
        self.rect = pygame.Rect(self.x,self.y,BLOCK_SIZE,BLOCK_SIZE)
        
    """
        summary: funkce pro pohyb ovoce
        - do prava
        - do leva
        - nahoru
        - dolu
        - pohyb ovoce o 10px
        - counter se zvetsi o 1
        - pokud je counter 25 nebo je ovoce na pravem okraji, tak se counter vynuluje a vybere se novy smer
        - pokud se ovoce dotkne hada, tak se counter vynuluje a vybere se novy smer
    """
    def update(self):
        #pokud se ovoce hybe
        if self.move:
            if self.counter <= 25:
                #do prava
                if self.rand == 1:
                    self.rect.x += 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.x >= 550:
                        self.counter = 0
                        self.rand = random.choice([2, 3, 4])
                    for rect in snake.body:
                        if self.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([2, 3, 4]) 
                #do leva
                if self.rand == 2:
                    self.rect.x -= 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.x <= 0:
                        self.counter = 0
                        self.rand = random.choice([1, 3, 4])
                    for rect in snake.body:
                        if self.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 3, 4]) 
                #nahoru
                if self.rand == 3:
                    self.rect.y -= 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.y <= 0:
                        self.counter = 0
                        self.rand = random.choice([1, 2, 4])
                    for rect in snake.body:
                        if self.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 2, 4]) 
                #dolu
                if self.rand == 4:
                    self.rect.y += 10
                    self.counter += 1
                    if self.counter == 25 or self.rect.y >= 550:
                        self.counter = 0
                        self.rand = random.choice([1, 2, 3])
                    for rect in snake.body:
                        if self.rect.colliderect(rect):
                            self.counter = 0
                            self.rand = random.choice([1, 2, 3]) 
        #kdyz se ovoce nehybe tak se nic neudpdatuje
        else:
            pass
        
    #kresli ovoce
    def draw(self):
        screen.blit(self.img, self.rect)
        #pygame.draw.rect(screen,RED,self.rect) 