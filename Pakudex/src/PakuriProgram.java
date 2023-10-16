import java.util.Scanner;

public class PakuriProgram {
    static public void main(String args[]){
        Scanner input = new Scanner(System.in);//Scanner object for user input
        System.out.println("Welcome to Pakudex: Tracker Extraordinaire!");
        int capacity;
        while(true){
            try{
                System.out.println("Enter max capacity of the Pakudex:");
                capacity = input.nextInt();
                if(capacity < 0){
                    System.out.println("Please enter a valid size.");
                    continue;
                }
            }
            catch(Exception e){
                System.out.println("Please enter a valid size.");
                input.next();
                continue;
            }
            break;
        }
        //loop to continue asking for maximum capacity until a valid size is entered
        System.out.println("The Pakudex can hold " + capacity + " species of Pakuri.");

        Pakudex pakumon = new Pakudex(capacity);//Pakudex object to call Pakudex methods
        String species;//String to set to user inputs
        boolean on = true;// determines if program is still running

        while(on) {//loop to continue running the system
            System.out.println("Pakudex Main Menu\n-----------------\n1.  List Pakuri\n2.  Show Pakuri\n3.  Add Pakuri\n4.  Evolve Pakuri\n5.  Sort Pakuri\n6.  Exit");
            //Pakudex menu printed
            System.out.println("What would you like to do?");
            String option = input.next();
            switch(option){//switch statement to go to correct option based on user input
                case "1":
                    if(pakumon.getSpeciesArray() == null){
                        System.out.println("No Pakuri in Pakudex yet!");
                    }
                    //checks to see if there is any Pakuri
                    else{
                        System.out.println("Pakuri In Pakudex:");
                        for(int i = 0; i < pakumon.getSpeciesArray().length; i++){
                            System.out.println((i + 1) + ". " + pakumon.getSpeciesArray()[i]);
                        }
                    }
                    //prints all Pakuri in the Pakudex on a list
                    break;
                case "2":
                    System.out.println("Enter the name of the species to display:");
                    species = input.next();
                    if(pakumon.getStats(species) == null){
                        System.out.println("Error: No such Pakuri!");
                    }
                    //checks to see Pakuri inputted is in Pakudex
                    else{
                        System.out.println("Species: " + species + "\nAttack: " + pakumon.getStats(species)[0] + "\nDefense: " + pakumon.getStats(species)[1] + "\nSpeed: " + pakumon.getStats(species)[2]);
                    }
                    //prints out the stats of specified Pakuri
                    break;
                case "3":
                    if(pakumon.getCapacity() > pakumon.getSize()) {//makes sure Pakudex has space
                        System.out.println("Enter the name of the species to add:");
                        species = input.next();
                        if (pakumon.addPakuri(species)) {
                            System.out.println("Pakuri species " + species + " successfully added!");
                        }
                        else{
                            System.out.println("Error: Pakudex already contains this species!");
                        }
                        //checks to see if Pakuri is not already in the Pakudex
                    }
                    else{
                        System.out.println("Error: Pakudex is full!");
                    }
                    break;
                case "4":
                    System.out.println("Enter the name of the species to evolve:");
                    species = input.next();
                    if(pakumon.evolveSpecies(species)){
                        System.out.println(species + " has evolved!");
                    }
                    else{
                        System.out.println("Error: No such Pakuri!");
                    }
                    //Checks to see if specified Pakuri is in Pakudex to be evolved
                    break;
                case "5":
                    pakumon.sortPakuri();
                    System.out.println("Pakuri have been sorted!");
                    //sorts the Pakudex in lexicographical order
                    break;
                case "6":
                    System.out.println("Thanks for using Pakudex! Bye!");
                    on =false;
                    //exits Pakudex
                    break;
                default:
                    System.out.println("Unrecognized menu selection!");
                    //default for any invalid option choices
            }
        }
    }
}
