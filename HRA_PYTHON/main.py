from assets import *
from funkce import *
from classes import *

from os.path import join,dirname,realpath
import pygame
import sys
import random
import os

pygame.init()

#cteni skore z textaku pokud existuje, jinak jse best_score 0
if os.path.exists('best_score.txt'):
    with open(join(dirname(realpath(__file__)), "best_score.txt"), "r") as file:
            best_score = int(file.read())
else:
    best_score=0   
#-------------------------main game loop-----------------------#
run = True

while run:
    
    if chosen_difficulty == 1:
        clock.tick(7)
    if chosen_difficulty == 2:
        clock.tick(10)
    if chosen_difficulty == 3:
        clock.tick(15)
            

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    """
        summary: funkce pro vykresleni menu
        - pokud je main_menu True, tak se vykresli menu
        - pokud je vybrany skin, tak se vykresli tlacitko pro pusteni hry
        - pokud se zmackne tlacitko pro pusteni hry, tak se vykresli had a ovoce
        - pokud se zmackne tlacitko pro vyber skinu, tak se vykresli menu pro vyber skinu
        - pokud se zmackne tlacitko pro vyber ovoce, tak se vykresli menu pro vyber ovoce
        - pokud se zmackne tlacitko pro vyber obtiznosti, tak se vykresli menu pro vyber obtiznosti
        - pokud se had dotkne sam sebe nebo okraje obrazovky, tak se vykresli game over
    """
    if main_menu == True:
        screen.blit(menu_sprite,(0,0))
        button1=Button(220, 300)
        button2=Button(220, 370)
        button3=Button(220, 440)
        button4=Button(220, 510)
        drawText("MAIN MENU!!", "comicsans",50,PINK, 135, 80)
        if chosen_fruit:
            button1.draw()
            drawText("Play game", "comicsans", 25, PINK, 245, 300)
        button2.draw()
        button3.draw()
        button4.draw()
        
        drawText("Skin", "comicsans", 25, PINK, 270, 370)
        drawText("Fruit", "comicsans", 25, PINK, 270, 440)
        drawText("Difficulty", "comicsans", 25, PINK, 240, 510)


        #kontroluje zmacknuti tlacitka pro spusteni hry
        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if chosen_fruit and chosen_head and chosen_tail and chosen_difficulty:
                if button1.rect.collidepoint(pygame.mouse.get_pos()):
                    main_menu=False
                    #kresli noveho hada a ovoce kazdou hru
                    snake=Snake(chosen_head, chosen_tail, chosen_color)
                    fruit = Fruit(chosen_fruit)
                    score=0

            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                menu_skins=True
                main_menu=False

            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                menu_fruit=True
                main_menu=False

            if button4.rect.collidepoint(pygame.mouse.get_pos()):
                menu_difficulty=True
                main_menu=False
            
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    elif menu_skins ==True:
        screen.blit(go_sprite,(0,0))
        drawText("CHOOSE A SKIN!!", "comicsans",50,WHITE, 80, 100)
        button1=Button(220, 275)
        button2=Button(220, 355)
        button3=Button(220, 435)
        button1.draw()
        button2.draw()
        button3.draw()
        screen.blit(pygame.transform.scale(head_sprite,(40,38)),(275,276))
        screen.blit(pygame.transform.scale(head2_sprite,(40,38)),(275,356))
        screen.blit(pygame.transform.scale(head3_sprite,(40,38)),(275,436))
        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if button1.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head_sprite
                chosen_tail= ocas_sprite
                chosen_color= PINK
                main_menu=True
                menu_skins=False
            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head2_sprite
                chosen_tail= ocas2_sprite
                chosen_color= GREEN
                main_menu=True
                menu_skins=False
            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_head= head3_sprite
                chosen_tail= ocas3_sprite
                chosen_color= BLUE
                main_menu=True
                menu_skins=False
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    elif menu_fruit == True:
        screen.blit(go_sprite,(0,0))
        drawText("CHOOSE A FRUIT!!", "comicsans",50,WHITE, 70, 100)
        button1=Button(220, 275)
        button2=Button(220, 355)
        button3=Button(220, 435)
        button1.draw()
        button2.draw()
        button3.draw()
        screen.blit(pygame.transform.scale(jablko_sprite,(40,40)),(275,275))
        screen.blit(pygame.transform.scale(hruska_sprite,(40,40)),(275,355))
        screen.blit(pygame.transform.scale(svestka_sprite,(40,40)),(275,435))

        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if button1.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= jablko_sprite
                main_menu=True
                menu_fruit=False
            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= hruska_sprite
                main_menu=True
                menu_fruit=False
            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                chosen_fruit= svestka_sprite
                main_menu=True
                menu_fruit=False
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    elif menu_difficulty == True:
        screen.blit(go_sprite,(0,0))
        drawText("CHOOSE A LEVEL!!", "comicsans",50,WHITE, 70, 100)
        button1=Button(220, 275)
        button2=Button(220, 355)
        button3=Button(220, 435)
        button1.draw()
        button2.draw()
        button3.draw()
        drawText("Easy", "comicsans", 25, PINK, 270, 275)
        drawText("Medium", "comicsans", 25, PINK, 255, 355)
        drawText("Hard", "comicsans", 25, PINK, 270, 435)

        if pygame.mouse.get_pressed()[0] and new_press:
            new_press = False
            if button1.rect.collidepoint(pygame.mouse.get_pos()):
                main_menu=True
                menu_difficulty=False
                chosen_difficulty = 1
            if button2.rect.collidepoint(pygame.mouse.get_pos()):
                main_menu=True
                menu_difficulty=False
                chosen_difficulty = 2
            if button3.rect.collidepoint(pygame.mouse.get_pos()):
                main_menu=True
                menu_difficulty=False
                chosen_difficulty = 3
        if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    else:
        if game_over==False:
            screen.blit(bg_sprite,(0,0))
            snake.move()
            snake.update()
            fruit.update()

            #kreslici funkce
            fruit.draw()
            snake.draw()
            drawText(str(score), "comicsans",50, WHITE, int(WIDTH/2), int(0))
            
        
            #kolize s ovocem
            if snake.head.colliderect(fruit.rect):
                last_block = snake.body[-1]
                snake.body.append(pygame.Rect(last_block.x, last_block.y, BLOCK_SIZE, BLOCK_SIZE))
                #skore (musi byt and generovanim noveho ovoce)
                if fruit.move:
                    score += 2
                else:
                    score += 1
                fruit = Fruit(chosen_fruit)
                pygame.mixer.Sound.play(eat_sound)
                

            #kolize s telem
            for rect in snake.body:
                if snake.head.x == rect.x and snake.head.y == rect.y:
                    game_over=True
                    pygame.mixer.Sound.play(over_sound)
            

            #kolize out of screen
            if snake.head.x>=WIDTH or snake.head.x<0 or snake.head.y>=HEIGHT or snake.head.y<0:
                game_over=True
                pygame.mixer.Sound.play(over_sound)

        """
            summary: vykresleni game over
            - pokud je game_over True, tak se vykresli game over, skore a tlacitka
            - pokud se zmackne tlacitko pro pusteni hry, tak se vykresli had a ovoce
            - pokud se zmackne tlacitko pro navrat do menu, tak se vykresli menu
        """
        if game_over==True:
            screen.blit(go_sprite,(0,0))
            button1=Button(230, 330)
            button2=Button(230, 400)
            drawText("GAME OVER!!", "comicsans",50,WHITE, 150, 100)
            drawText("SCORE: "+str(score), "comicsans",36,WHITE, 230, 200)
            button1.draw()
            button2.draw()
            drawText("Main menu", "comicsans", 25, PINK, 245, 330)
            drawText("Play again", "comicsans", 25, PINK, 250, 400)
            #pokud je skore vetsi jak best skore, tak se v textaku prepise
            if score>best_score:
                best_score = score
                with open(join(dirname(realpath(__file__)), "best_score.txt"), "w") as file:
                    file.write(str(best_score))
            drawText("High score: " + str(best_score), "comicsans", 25, WHITE, 240, 250)

            if pygame.mouse.get_pressed()[0] and new_press:
                new_press = False
                if button2.rect.collidepoint(pygame.mouse.get_pos()):
                    game_over=False
                    score = 0
                    snake = Snake(chosen_head, chosen_tail, chosen_color)
                    fruit = Fruit(chosen_fruit)

                if button1.rect.collidepoint(pygame.mouse.get_pos()):
                    main_menu=True
                    menu_skins = False
                    menu_fruit=False
                    game_over=False

            if not pygame.mouse.get_pressed()[0] and not new_press:
                new_press = True

    pygame.display.update()

pygame.quit()