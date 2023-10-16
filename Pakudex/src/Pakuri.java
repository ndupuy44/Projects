public class Pakuri {

    private String _species;
    private int attack;
    private int defense;
    private int speed;
    //variables for Pakuri attributes

    public Pakuri(String species){
        _species = species;
        attack = (species.length() * 7) + 9;
        defense = (species.length() * 5) + 17;
        speed = (species.length() * 6) + 13;
    }
    //Pakuri constructor assigns species name, attack, defense, and speed

    public String getSpecies(){
        return _species;
    }
    //returns species

    public int getAttack(){
        return attack;
    }
    //returns Pakuri attack

    public int getDefense(){
        return defense;
    }
    //returns Pakuri defense

    public int getSpeed(){
        return speed;
    }
    //returns Pakuri speed

    public void setAttack(int newAttack){
        attack = newAttack;
    }
    //sets new attack for Pakuri

    public void evolve(){
        attack = attack * 2;
        defense = defense * 4;
        speed = speed * 3;
    }
    //evolves Pakuri upping attack, defense, and speed
}
