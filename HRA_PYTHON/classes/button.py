import pygame
from assets import *

"""
    summary: trida pro tlacitka
    x -> x pozice tlacitka
    y -> y pozice tlacitka
    color -> barva tlacitka
    width -> sirka tlacitka
    height -> vyska tlacitka
    rect -> obdelnik tlacitka
"""

class Button():     
    def __init__(self, x: int, y: int):
        self.color = WHITE
        self.width = 160
        self.height = 40
        self.x = x
        self.y = y
        self.rect = pygame.rect.Rect((self.x, self.y), (self.width, self.height)) 

    def draw(self):
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.width, self.height))