from sueca_suits_ranks import valid_rank, valid_suit, rank_points, rank_higher_than

class Card:
    
    def __init__(self, rank, suit):
        self.Rank = rank
        self.Suit = suit
    
    def points(self):
        ''''Returns the points of a card object'''
        return rank_points(self.Rank)
    
    def higher_than(self, other, s, t):
        '''Deduces whether the card self has a higher rank than the card other with respect to the lead suit, s, and the trump suit, t'''
        if not(valid_suit(s)):
            raise ValueError('Invalid suit symbol ' + s)
        elif not(valid_suit(t)):
            raise ValueError('Invalid suit symbol '  + t)
        else:
            if self.Suit == other.Suit:
                return rank_higher_than(self.Rank, other.Rank)
            else: 
                if other.Suit == t or other.Suit == s and self.Suit != t:
                    return False
                else:
                    return True
                                   
    def show(self):
        '''Returns the string representation of a card object'''
        cstr = self.Rank + self.Suit
        return cstr
       
def parseCard(cs):
    '''Returns a card object from a string, cs'''
    try:
        len(cs)
    except TypeError:
        raise CardInvalid(cs, 'Card string must only consist of two characters')
    if len(cs) != 2:
        raise CardInvalid(cs, 'Card string must only consist of two characters')
    else:
        r, s = cs
        if not(valid_rank(r)):
            raise CardInvalid(cs, 'Invalid rank symbol ' + r)
        elif not(valid_suit(s)):
            raise CardInvalid(cs, 'Invalid suit symbol ' + s)
        else:
            return Card(r, s)

class CardInvalid(Exception):
    ''''Custom excpection for invalid cards'''
    def __init__(self, cs, ermsg=' '):
        str1 = 'Invalid card string {s} \n' + ermsg
        self.msg = str1.format(s = cs)
        super().__init__(self.msg)
    