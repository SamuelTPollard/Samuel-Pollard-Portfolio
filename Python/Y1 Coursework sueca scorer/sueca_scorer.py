from sueca_suits_ranks import suit_full_name
from sueca_cards import CardInvalid
from sueca_tricks import parseGameFile
from sueca_games import Game, IllegalCardPlayed, DealerDoesNotHaveTrumpCard, CardAlreadyPlayed, SuecaGameIncomplete

def runGame(fname, showCards = False, showGame = False):
    'Displays the score and winning pair of the same by defual, showCards is whether the cards of each playe are shown, showGame is whether the trump card and tricks of the game area shown.'
    CheckFile(fname)
    trump, tricks = parseGameFile(fname)
    game = Game(trump, tricks)
    try:
        game.CheckForErrors()
        print('\n')
    except IllegalCardPlayed as text:
        text = str(text)
        print(text)
        player = int(text[7])
        if player % 2 == 0:
            print('Pair A won the given sueca game.')
            print('120 | 0')
        else:
            print('Pair B won the given sueca game')
            print('0 | 120')
    except SuecaGameIncomplete as text2:
        print(text2)
        GA, GB = game.score()
        print('Current score: (' + str(GA) +  ', ' + str(GB) + ')')  
    else:
        GA, GB = game.score()
        if GA > GB:
            print('Pair A won the given game.')
        elif GB > GA:
            print('Pair B won the given game.')
        else:
            print('The game resulted in a draw')
        print('(' + str(GA) +  ', ' + str(GB) + ')' )
    finally:
        if showCards:
            print('\nPlayer\'s cards in the sueca game:')
            for p in range(1, 5):
                str1 = 'Player {p}: ' + ', '.join(game.cardsOfstr(p))
                print(str1.format(p = p))
        if showGame:
            winners = game.score(True)
            print('\nTrump: '  + game.gameTrump().show() + ' - ' + suit_full_name(game.trump.Suit))
            for t in range(0, len(game.tricks)):
                print((str(t+1)) + ':  ' + (game.gameTricks()[t].show()) + " - winner : " + str(winners[t]))
            print('Player win tally:')
            for p in range(0, 4):
                count = 0
                for x in winners:
                    if x == p + 1:
                        count += 1
                print('Player ' + str(p+1) + ": " + str(count))
                
def CheckFile(fname):
    isfile = False
    if fname[-5:] != 'sueca':
        for x in fname:
            if x == '.':
                dotind = fname.index(x)
                isfile = True
        if not(isfile):
            raise NotAFile(fname)
        extension = fname[dotind:]
        raise InvalidFileType(extension)
    try:
        open(fname)
    except FileNotFoundError:
        raise GameFileCouldNotBeFound(fname)
    
    
class GameFileCouldNotBeFound(Exception):
    '''Custom error for when a game file cannot be found'''
    def __init__(self, fs):
        str1 = 'Could not find the game file \'{f}\'' 
        self.msg = str1.format(f = fs)
        super().__init__(self.msg)

class InvalidFileType(Exception):
    '''Custom excpetion for ensuring only sueca files are pass into sueca scorer'''
    def __init__(self, xs):
        str1 = 'Invalid file type \'{xs}\', file must be of type \'.sueca \''
        self.msg = str1.format(xs = xs)
        super().__init__(self.msg)

class NotAFile(Exception):
    '''Custom exception for detecting if a non-file string is given'''
    def __init__(self, fs):
        str1 = 'The string {s} is not a file'
        self.msg = str1.format(s = fs)
        super().__init__(self.msg)
     
#%%

def scorerloop():
    '''Command line interface for sueca scorer'''
    
    valid = False
    while not(valid):
        '''Loop for ensuring a valid sueca game file is entered by the user'''
        filename = input('Enter a sueca game file path \n>>> ')
        try:
            CheckFile(filename)
        except GameFileCouldNotBeFound:
            print('File, \'' + filename +'\' ,could not be found')
        except InvalidFileType:
            print('File, \'' + filename + '\' is not a sueca game file')
        except NotAFile:
            print('\'' + filename +  '\' is not a file')
        else:
            break
    
    while not(valid):
        '''Loop for ensuring either y or n is entered by the user'''
        showcards = input('Do you want the cards of each player to be shown? [y/n] \n>>> ')
        if showcards.lower() == 'y':
            showcards = True
            break
        elif showcards.lower() == 'n':
            showcards = False
            break
        else:
            print('Invalid value, please type either y or n')
            
    while not(valid):
        '''Loop for ensuring either y or n is entered by the user'''
        showgame = input('Do you want the cards of each trick to be shown? [y/n] \n>>> ')
        if showgame.lower() == 'y':
            showgame = True
            break
        elif showgame.lower() == 'n':
            showgame = False
            break
        else:
            print('Invalid value, please type either y or n')
    
    # Calls function with the options chosen by the user including error messages as strings
    try:
        runGame(filename, showcards, showgame)
    except DealerDoesNotHaveTrumpCard as e1:
        print(e1)
    except CardAlreadyPlayed as e2:
        print(e2)
    except CardInvalid as e3:
        print(e3)
    except SuecaGameIncomplete as e4:
        print(e4)
    finally:
        while not(valid):
            '''Loop for ensuring asking the player whether they want to restart the program'''
            showgame = input('Do you want to find the score of another file? [y/n] \n>>> ')
            if showgame.lower() == 'y':
                scorerloop()
                break
            elif showgame.lower() == 'n':
                break
            else:
                print('Invalid value, please type either y or n')

scorerloop()