import java.util.Scanner;//importing scanner

public class Blackjack {
    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        P1Random rng = new P1Random();
        boolean playing = true, inGame;
        int gameCount = 1;
        int numWin = 0;
        int dealerWin = 0;
        int numTie = 0;
        //Variables declared to keep tract of game data
        while(playing){
            System.out.println("START GAME #" + gameCount);
            int myNum = 0;
            int cardValue = rng.nextInt(13) + 1;
            if(cardValue > 10){
                myNum = 10;
            }
            else {
                myNum = cardValue;
            }
            switch(cardValue){
                case 1:
                    System.out.println("\nYour card is a ACE!");
                    break;
                case 11:
                    System.out.println("\nYour card is a JACK!");
                    break;
                case 12:
                    System.out.println("\nYour card is a Queen!");
                    break;
                case 13:
                    System.out.println("\nYour card is a KING!");
                    break;
                default:
                    System.out.println("\nYour card is a " + cardValue + "!");
            }
            //switch statement for face cards
            System.out.println("Your hand is: " + myNum + "\n");
            inGame = true;
            while(inGame){//nested loop to prevent Start game from popping up everytime
                System.out.println("\n1.  Get another card\n2.  Hold hand\n3.  Print statistics\n4.  Exit");
                System.out.println("\nChoose an option:");
                //option menu
                int choice = input.nextInt();
                if(choice == 1){
                    cardValue = rng.nextInt(13) + 1;
                    if(cardValue > 10){
                        myNum = myNum + 10;
                    }
                    else {
                        myNum = myNum + cardValue;
                    }
                    //if statements to add proper values of cards
                    if(myNum == 21){//when players obtains blackjack
                        switch(cardValue){
                            case 1:
                                System.out.println("Your card is a ACE!\nYour hand is: 21\n\nBLACKJACK! You win!");
                                break;
                            case 11:
                                System.out.println("Your card is a JACK!\nYour hand is: 21\n\nBLACKJACK! You win!");
                                break;
                            case 12:
                                System.out.println("Your card is a QUEEN!\nYour hand is: 21\n\nBLACKJACK! You win!");
                                break;
                            case 13:
                                System.out.println("Your card is a KING!\nYour hand is: 21\n\nBLACKJACK! You win!");
                                break;
                            default:
                                System.out.println("Your card is a " + cardValue + "!\nYour hand is: 21\n\nBLACKJACK! You win!");
                        }
                        //switch statement for face cards
                        gameCount = gameCount + 1;
                        numWin = numWin + 1;
                        inGame = false;
                        //resets game adding one to game counter and player wins
                    }
                    if(myNum > 21){//when player bust
                        switch(cardValue){
                            case 1:
                                System.out.println("Your card is a ACE!\nYour hand is: " + myNum + "\n\nYou exceeded 21! You lose.");
                                break;
                            case 11:
                                System.out.println("Your card is a JACK!\nYour hand is: " + myNum + "\n\nYou exceeded 21! You lose.");
                                break;
                            case 12:
                                System.out.println("Your card is a QUEEN!\nYour hand is: " + myNum + "\n\nYou exceeded 21! You lose.");
                                break;
                            case 13:
                                System.out.println("Your card is a KING!\nYour hand is: " + myNum + "\n\nYou exceeded 21! You lose.");
                                break;
                            default:
                                System.out.println("Your card is a " + cardValue + "!\nYour hand is: " + myNum + "\n\nYou exceeded 21! You lose.");
                        }
                        //switch statement for face cards
                        gameCount = gameCount + 1;
                        dealerWin = dealerWin + 1;
                        inGame = false;
                        //resets game adding one to game counter and dealer wins
                    }
                    if(myNum < 21){
                        switch(cardValue){
                            case 1:
                                System.out.println("\nYour card is a ACE!");
                                break;
                            case 11:
                                System.out.println("\nYour card is a JACK!");
                                break;
                            case 12:
                                System.out.println("\nYour card is a Queen!");
                                break;
                            case 13:
                                System.out.println("\nYour card is a KING!");
                                break;
                            default:
                                System.out.println("\nYour card is a " + cardValue + "!");
                        }
                        //switch statement for face cards
                        System.out.println("Your hand is: " + myNum + "\n");
                        //prints out players hand
                    }
                }
                else if(choice == 2){
                    int dHand = rng.nextInt(11) + 16;
                    System.out.println("Dealer's hand: " + dHand);
                    System.out.println("Your hand is: " + myNum);
                    //prints out players and dealers hand
                    if(dHand > 21){//if dealer bust
                        System.out.println("\nYou win!");
                        gameCount = gameCount + 1;
                        numWin = numWin + 1;
                        inGame = false;
                        //prints player wins and reset game adding one to player win and game count
                    }
                    else if(myNum > dHand){//if player beats dealer
                        System.out.println("\nYou win!");
                        gameCount = gameCount + 1;
                        numWin = numWin + 1;
                        inGame = false;
                        //prints player wins and reset game adding one to player win and game count
                    }
                    else if(dHand > myNum){//if dealer beats player
                        System.out.println("\nDealer wins!");
                        gameCount = gameCount + 1;
                        dealerWin = dealerWin + 1;
                        inGame = false;
                        //prints dealer wins and reset game adding one to dealer win and game count
                    }
                    else{
                        System.out.println("\nIt's a tie! No one wins!");
                        gameCount = gameCount + 1;
                        numTie = numTie + 1;
                        inGame = false;
                        //else for in case of ties adding one to numTies and game count
                    }
                }
                else if(choice == 3){
                    System.out.println("Number of Player wins: " + numWin +
                            "\nNumber of Dealer wins: " + dealerWin + "\nNumber of tie games: " + numTie +
                            "\nTotal # of games played is: " + (gameCount-1) + "\nPercentage of Player wins: " + 100*(double)numWin/(gameCount-1) + "%");
                    //prints out player statistics
                }
                else if(choice == 4){
                    inGame = false;
                    playing = false;
                    //ends program
                }
                else{
                    System.out.println("Invalid input!\nPlease enter an integer value between 1 and 4.");
                    //for invalid menu options
                }
            }
        }
    }
}
