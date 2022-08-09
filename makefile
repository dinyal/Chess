chess: ChessMain.o ChessBoard.o piece.o king.o queen.o knight.o bishop.o rook.o pawn.o helper.o
	g++ -g ChessMain.o ChessBoard.o piece.o king.o queen.o knight.o bishop.o rook.o pawn.o helper.o -o chess

ChessBoard.o: ChessBoard.cpp ChessBoard.h piece.h helper.h
	g++ -Wall -Wextra -g -c ChessBoard.cpp

piece.o: piece.cpp piece.h ChessBoard.h helper.h
	g++ -Wall -Wextra -g -c piece.cpp

king.o: king.cpp king.h piece.h
	g++ -Wall -Wextra -g -c king.cpp

queen.o: queen.cpp queen.h piece.h
	g++ -Wall -Wextra -g -c queen.cpp

knight.o: knight.cpp knight.h piece.h
	g++ -Wall -Wextra -g -c knight.cpp

bishop.o: bishop.cpp bishop.h piece.h
	g++ -Wall -Wextra -g -c bishop.cpp

rook.o: rook.cpp rook.h piece.h
	g++ -Wall -Wextra -g -c rook.cpp

pawn.o: pawn.cpp pawn.h piece.h
	g++ -Wall -Wextra -g -c pawn.cpp

helper.o: helper.cpp helper.h
	g++ -Wall -Wextra -g -c helper.cpp

ChessMain.o: ChessMain.cpp ChessBoard.h
	g++ -Wall -Wextra -g -c ChessMain.cpp

clean:
	rm *.o chess