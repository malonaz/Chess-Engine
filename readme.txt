################################################################################
##################### WELCOME TO MY CHESS PROGRAM ##############################
################################################################################



################################################################################
################################# CASTLING #####################################
################################################################################
Looking through my code, you will notice that for castling, the only
conditions I check to ensure my king is safe are simply:

   1) check the the one square the king will travel through in order to move to
      its castled position is not threatened. I check for this condition because
      it is not checked anywhere else in the program as it is specific to this
      king move only.
      
   2) whether the king is in check before the move. This position will never 
      come up as no move that puts the king in check is permitted but without 
      this check, this allows the king to castle out of check, which is not
      legal as per chess rules.

The reason why I don't implement further condition checks such as: does moving 
the rook expose my king is that in order for the castle move to be legal, the 
rook must have never moved. Its starting position is always in a corner, hence
its move cannot discover any check.

################################################################################
################################ EN PASSANT ####################################
################################################################################

In order to make sure my en passant move does not expose my king to check, I
could save then remove the pointer of the piece being taken en passant, and
manually move the pawn taking en passant to its new position, then evaluate if
king is in check. This is actually how I have originally implemented it.
However, I realized that there is only one scenario that is 
