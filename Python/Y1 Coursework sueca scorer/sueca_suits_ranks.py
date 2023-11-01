ranks = ['A',  '2', '3', '4', '5', '6', '7', 'Q', 'J', 'K']
suits = ['C', 'D', 'H', 'S']
suit_full_names = ['Clubs', 'Diamonds', 'Hearts', 'Spades']

def valid_suit(s):
    '''Returns whether a given suit string is valid'''
    return s in suits

def suit_full_name(s):
    '''Returns the full name of a suit given its suit character'''
    try:
        s[0]
    except TypeError:
        raise ValueError('Invalid suit symbol, ' + str(s))
    if not(valid_suit(s)):
        raise ValueError('Invalid suit symbol ' +  s)
    else:
        for i in suit_full_names:
            if i[0] == s:
                    return i

def valid_rank(r):
    '''Returns whether a given rank string is valid'''
    try:
        r[-1]
    except TypeError:
        raise ValueError('Invalid rank symbol ' + str(r))
    return r in ranks

def rank_points(r):
    '''Returns the points of a given rank of card'''
    try:
        r[-1]
    except TypeError or NameError:
        raise ValueError('Invalid rank symbol ' + str(r))
    else:
        if not(valid_rank(r)):
            raise ValueError('Invalid rank symbol ' + r)
        else:
            if r == 'A':
                return 11
            elif r == '7':
                return 10
            elif r == 'K':
                return 4
            elif r == 'J':
                return 3
            elif r == 'Q':
                return 2
            else:
                return 0
        
def rank_higher_than(r1, r2):
    '''Returns whether the points of the rank r1 are higher than that of r2'''
    if not(valid_rank(r1)):
        raise ValueError('Invalid rank symbol ' + r1)
    elif not(valid_rank(r2)):
        raise ValueError('Invalid rank symbol ' + r2) 
    else:
        if rank_points(r1) > rank_points(r2):
            return True
        elif rank_points(r1) == rank_points(r2):
            if ranks.index(r1) > ranks.index(r2):
                return True
        else:
            return False
    