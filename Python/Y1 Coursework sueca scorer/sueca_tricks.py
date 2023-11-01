from sueca_cards import parseCard

class Trick:
    
    def __init__(self, Cards):
        self.Cards = Cards
    
    def points(self):
        '''Finds the points of the given trick'''
        pointsum = 0
        for x in self.Cards:
            pointsum += x.points()
        return pointsum
                                   
    def trick_winner(self, t, startplayer = 1):
        ''''Finds the winner of the given trick, with respect to the trump card, t, and the previous tricks winner'''
        Cards = self.show().split(' ')
        l = Cards[0][1]
        wincard = Cards[0]
        for x in range(0, 3):
            c2 = parseCard(Cards[x+1])
            if c2.higher_than(parseCard(wincard), l, t):
                wincard = Cards[x+1]
        winner = Cards.index(wincard) + startplayer 
        if winner > 4:
            winner -= 4
        return winner
            
    def show(self):
        ''''Shows the cards of the given trick'''
        c = []
        for x in self.Cards:
            c.append(x.show())
        return ' '.join(c)
            
def parseTrick(cs):
    '''Creates a trick object consisting of 4 card strings seperated by space e.g. 'SR SR SR SR' '''
    seperate = cs.split(' ')
    if  len(seperate) != 4:
        raise ValueError(' A trick string must comprise four cards only; the given trick is: ' + cs)
    else:
        cards = []
        for x in seperate:
            cards.append(parseCard(x))
        return Trick(cards)
            
def parseGameFile(fname):
    '''Returns the trump suit and tricks of a given sueca game file'''
    f = open(fname, 'r')
    Trump = f.readline(5).strip()
    if Trump == '':
        return 'Trump not found in game file'
    l = []
    for y in f:
        if y.strip() != '':
            t = parseTrick(y[:-1])
            l.append(t)
    f.close()
    return parseCard(Trump), l
