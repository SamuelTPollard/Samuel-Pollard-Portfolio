from sueca_suits_ranks import suit_full_name
from sueca_cards import parseCard
from sueca_tricks import parseTrick

class Game:
    
    def __init__(self, trump, tricks = []):
        self.trump = trump
        self.tricks = tricks
    
    def gameTrump(self):
        '''Returns the trump card of the game, self'''
        return self.trump
    
    def score(self, getwinner=False):
        '''Returns the score of the game file games in the form [Group A - P1 and P3, Group B - P2 and P4]'''
        score = [0, 0]
        winner = 1
        winners = []
        for x in self.tricks:
            winner = x.trick_winner(self.trump.Suit, winner)
            winners.append(winner)
            trickscore = x.points()
            if winner % 2 == 1:
                score[0] += trickscore
            else:
                score[1] += trickscore
        if not(getwinner):
            return score
        else:
            return winners
                
    def playTrick(self, t):
        '''Adds the trick, t, to the game, self'''
        length = len(self.tricks)
        if length == 10:
            return 'Game already complete'
        else:
            for c in t:
                for p in range(1, 5):
                    pc = self.cardsOfstr(p)
                    if pc == c:
                        raise CardAlreadyPlayed(pc)
            self.tricks.append(parseTrick(t))
            
    def CheckForErrors(self):
        length = len(self.tricks)
        if length != 10:
            raise SuecaGameIncomplete(length)
        else:
            self.Check_For_Already_Played_Card()
            self.Check_For_Trump_In_Dealer_Cards()
            self.IllegalCutDetector()
            
    def cardsOf(self, p):
        '''Returns the cards of a given player, p'''
        if p < 1 or p > 4:
            raise ValueError('Invalid player number ' + str(p))
        l = []
        prevwinner = 0
        p -= 1
        for x in self.tricks:
            playerind = - prevwinner + p
            l.append(parseCard(x.show().split(' ')[playerind]))
            prevwinner = x.trick_winner(self.trump.Suit, prevwinner) 
        return l
    
    def cardsOfstr(self, p):
        '''Returns the card string of a given player, p'''
        pcards = []
        for x in self.cardsOf(p):
            pcards.append(x.show())
        return pcards
    
    def gameTricks(self):
        '''Returns the tricks of the game self'''
        trickobs = []
        for x in self.tricks:
            trickobs.append(x)
        return trickobs
    
    def Check_For_Already_Played_Card(self):
        '''Checks for duplicate cards in a game'''
        for p in range(1, 5):
            for p2 in range(1, 5):
                pcards = self.cardsOfstr(p)
                p2cards = self.cardsOfstr(p2)
                if pcards != p2cards:
                    for pc in pcards:
                        for p2c in p2cards:
                            if pc == p2c:
                                raise CardAlreadyPlayed(pc)
                        
    def Check_For_Trump_In_Dealer_Cards(self):
        '''Checks to see whether the dealer, player 2, has the trump card in their hand'''
        trumpfound = False
        for y in self.cardsOfstr(2):
            if y == self.trump.show():
                trumpfound = True
        if not(trumpfound):
            raise DealerDoesNotHaveTrumpCard(self.trump)

    def IllegalCutDetector(self):
        '''Checks whether an illegal cut has been performed'''
        trumpsuit = self.trump.Suit
        for x in self.tricks:
            trickcards = x.show().split(' ')
            leadsuit = trickcards[0][1]
            for y in trickcards:
                if y[1] == trumpsuit and trumpsuit != leadsuit:
                    for p in range(1, 5):
                        playercards = self.cardsOfstr(p)
                        if y in playercards:
                            trumpindex = playercards.index(y)
                            cutcards = playercards[trumpindex + 1:]
                            for z in cutcards:
                                if z[1] == leadsuit:
                                    raise IllegalCardPlayed(y, leadsuit, p, trumpindex + 1)
                                    

class CardAlreadyPlayed(Exception):
    '''Custom excpection for when a card that has already been played is player  again'''
    def __init__(self, cs):
        str1 = 'Card, {s}, has already been played' 
        self.msg = str1.format(s = cs)
        super().__init__(self.msg)
        
class DealerDoesNotHaveTrumpCard(Exception):
    '''Custom excpection for when the trump card is not found in the dealer's (player 2) hand'''
    def __init__(self, trump):
        str1 = 'Player 2 (Dealer) does not hold trump card {ts}' 
        self.msg = str1.format(ts = trump.show())
        super().__init__(self.msg)

class IllegalCardPlayed(Exception):
    '''Custom excpection for detecting when an illegal cut is made'''
    def __init__(self, cs, ls, p, r):
        str1 = 'Player {p} played illegal card {c} in round {r} with respect to the lead suit {l}' 
        self.msg = str1.format(c = cs, l = suit_full_name(ls), p = p, r = r)
        super().__init__(self.msg)
        
class SuecaGameIncomplete(Exception):
    '''Custom excpection for detecting if a game has not finsihed'''
    def __init__(self, tn):
        str1 = 'The game is incomplete, only {n} tricks have been played out of 10' 
        self.msg = str1.format(n = tn)
        super().__init__(self.msg)
