import pygame
from assets import *

"""
    summary: trida pro hada
    img1 -> hlava hada
    img2 -> ocas hada
    color -> barva tela hada
    x -> x pozice hlavy
    y -> y pozice hlavy
    x_dir -> smer pohybu x
    y_dir -> smer pohybu y
    head -> obdelnik hlavy
    body -> pole obdelniku tela
    old_dir -> promenna pro uchovani posledniho smeru pohybu
    img_head -> obrazek hlavy
    img_ocas -> obrazek ocasu
    color -> barva tela hada
"""
class Snake():
    #img1 je hlava, img2 je ocas
    def __init__(self, img1, img2, color):
        self.x,self.y = BLOCK_SIZE,BLOCK_SIZE
        self.x_dir = 1
        self.y_dir = 0
        self.head = pygame.Rect(self.x,self.y,BLOCK_SIZE,BLOCK_SIZE)
        self.body = [pygame.Rect(self.x-BLOCK_SIZE,self.y,BLOCK_SIZE,BLOCK_SIZE) for _ in range(2)]
        self.old_dir = "d"
        self.img_head = img1
        self.img_ocas = img2
        self.color = color

    """
        summary: funkce pro vykresleni hada
        rotace hlavy:
        - do prava: pokud se had hybe do prava, tak se hlava vykresli normalne
        - dolu: pokud se had hybe dolu, tak se hlava vykresli o 270 stupnu otocena
        - do leva: pokud se had hybe do leva, tak se hlava vykresli o 180 stupnu otocena
        - nahoru: pokud se had hybe nahoru, tak se hlava vykresli o 90 stupnu otocena
    """
    def draw(self):
        #rotace hlavy
        #do prava
        if self.x_dir == 1 and self.y_dir==0:
            screen.blit(self.img_head, self.head)
        #dolu
        if self.x_dir == 0 and self.y_dir==1:
            screen.blit(pygame.transform.rotate(self.img_head,270), self.head)
        #do leva
        if self.x_dir == -1 and self.y_dir==0:
            screen.blit(pygame.transform.rotate(self.img_head,180), self.head)
        #nahoru
        if self.x_dir == 0 and self.y_dir==-1:
            screen.blit(pygame.transform.rotate(self.img_head,90), self.head)
            
        #kresleni tela
        for rect in self.body[1:]:
            pygame.draw.rect(screen, self.color, rect)
        
        """
            summary: funkce pro vykresleni ocasu
            rotace ocasu:
            - do prava: pokud se had hybe do prava, tak se ocas vykresli normalne
            - dolu: pokud se had hybe dolu, tak se ocas vykresli o 270 stupnu otocen
            - do leva: pokud se had hybe do leva, tak se ocas vykresli o 180 stupnu otocen
            - nahoru: pokud se had hybe nahoru, tak se ocas vykresli o 90 stupnu otocen
        """
        #rotace ocasu
        #do prava
        if self.body[0].x +BLOCK_SIZE == self.body[1].x and self.body[0].y == self.body[1].y:
            screen.blit(self.img_ocas, self.body[0])
        #dolu
        if self.body[0].x == self.body[1].x and self.body[0].y+BLOCK_SIZE == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,270), self.body[0])
        #do leva
        if self.body[0].x-BLOCK_SIZE == self.body[1].x and self.body[0].y == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,180), self.body[0])
        #nahoru
        if self.body[0].x == self.body[1].x and self.body[0].y-BLOCK_SIZE == self.body[1].y:
            screen.blit(pygame.transform.rotate(self.img_ocas,90), self.body[0])
        

    """
        summary: funkce pro pohyb hada
        - w -> nahoru
        - a -> do leva
        - s -> dolu
        - d -> do prava
    """
    def move(self):
        key = pygame.key.get_pressed()
        if key[pygame.K_w]:
            if self.old_dir != "s":
                self.y_dir = -1
                self.x_dir = 0
                self.old_dir="w"
        if key[pygame.K_a]:
            if self.old_dir != "d":
                self.y_dir = 0
                self.x_dir = -1
                self.old_dir="a"
        if key[pygame.K_d]:
            if self.old_dir != "a":
                self.y_dir = 0
                self.x_dir = 1
                self.old_dir="d"
        if key[pygame.K_s]:
            if self.old_dir != "w":
                self.y_dir = 1
                self.x_dir = 0
                self.old_dir="s"
        
    def update(self):
        self.body.append(self.head)
        for i in range(0,len(self.body)-1):
            self.body[i].x, self.body[i].y = self.body[i+1].x,self.body[i+1].y
        self.head.x += self.x_dir * BLOCK_SIZE
        self.head.y += self.y_dir * BLOCK_SIZE
        self.body.remove(self.head)