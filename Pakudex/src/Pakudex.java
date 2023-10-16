public class Pakudex {

    private Pakuri[] creatures;
    private int _capacity;

    public Pakudex(){
        _capacity = 20;
        creatures = new Pakuri[20];
    }
    //Pakudex default constructor sets the capacity of the Pakuri to 20

    public Pakudex(int capacity){
        _capacity = capacity;
        creatures = new Pakuri[capacity];
    }
    //Pakudex constructor sets capacity for Pakuri to user input passed through parameter

    public int getSize(){
        int size = 0;
        for(int i = 0; i < creatures.length; i++){
            if(creatures[i] != null){
                size++;
            }
            else{
                break;
            }
        }
        return size;
    }
    //runs through Pakuri array returning filled spaces to get number of species

    public int getCapacity(){
        return _capacity;
    }
    //returns maximum capacity that can be held in Pakudex

    public String[] getSpeciesArray(){
        if (creatures[0] == null) {
            return null;
        }
        String[] names = new String[getSize()];
        for(int i =0; i < names.length; i++){
            names[i] = creatures[i].getSpecies();
        }
        return names;
    }
    //returns an array of the Pakuri species utilizing getSize method to make size for returned array

    public int[] getStats(String species){
        int[] stats = new int[3];
        for(int i = 0; i < creatures.length; i++){
            try{
                if(creatures[i].getSpecies().equals(species)){
                    stats[0] = creatures[i].getAttack();
                    stats[1] = creatures[i].getDefense();
                    stats[2] = creatures[i].getSpeed();
                    return stats;
                }
            }
            catch (Exception e){
                break;
            }
        }
        return null;
    }
    //test to find species passed through in parameter then returns the attack, defense, and speed in an array
    //returns null if the the species is not in the Pakudex

    public void sortPakuri(){
        for(int i = 0; i < creatures.length - 1; i++){
            if(creatures[i] == null){
                break;
            }
            for(int j = i + 1; j < creatures.length; j++){
                try {
                    if ((creatures[i].getSpecies()).compareTo(creatures[j].getSpecies()) > 0) {
                        Pakuri temp = creatures[i];
                        creatures[i] = creatures[j];
                        creatures[j] = temp;
                    }
                }
                catch(Exception e){
                    break;
                }
            }
        }
    }//cycles through creatures array using .compareTo method on species name to sort Creatures array in lexicographical order

    public boolean addPakuri(String species){
        for(int i = 0; i < creatures.length; i++){
            if(creatures[i] == null){
                Pakuri newSpecies = new Pakuri(species);
                creatures[i] = newSpecies;
                break;
            }
            if(creatures[i].getSpecies().equals(species)){
                return false;
            }
        }
        return true;
    }
    //runs through creatures array looking for open spot to add Pakuri into creatures array and returns true
    //will return false if specified species equals another species in the creatures array

    public boolean evolveSpecies(String species){
        for(int i = 0; i < creatures.length; i++){
            try{
                if (creatures[i].getSpecies().equals(species)){
                    creatures[i].evolve();
                    return true;
                }
            }
            catch (Exception e){
                break;
            }
        }
        return false;
    }
    //cycles through creatures array looking for specified species and evoles that Pakuri returning true
    //If no species exist methoud returns false
}
