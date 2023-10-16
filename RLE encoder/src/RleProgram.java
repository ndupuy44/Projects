import java.util.Scanner;//imports scanner

public class RleProgram {
    public static String toHexString(byte[] data){
        String hexString = "";
        for(int i = 0; i < data.length; i++){
            int x = (int)data[i];
            hexString = hexString.concat(Integer.toHexString(x));
        }
        //runs through byte array changing every index to a hex creating a string
        return hexString;
    }
    //takes in byte array and returns a hexstring composed of the byte values

    public static int countRuns(byte[] flatData){
        int count = 1;
        int group = 1;
        for(int i = 0; i < flatData.length - 1; i++){
            if(flatData[i] == flatData[i+1]){//checks to see if run is continuing
                count++;
            }
            else{//resets run if new run starts
                group++;
                count = 1;
            }//resets run if 15 or more values repeat
            if(count >= 15){
                group++;
                count = 1;
            }
        }
        //runs through byte arrray checking for runs
        return group;
    }
    //returns the number of runs contained in flatdata array

    public static byte[] encodeRle(byte[] flatData){
        byte[] encoded = new byte[2*countRuns(flatData)];//makes new array based on runs of flat data array
        int count = 1;
        int index = 0;
        for(int i =0; i < flatData.length - 1; i++){
            if(flatData[i] == flatData[i+1]){
                count++;
            }
            //increases length of run if next index matches current index
            else{
                encoded[index] = (byte)count;
                encoded[index + 1] = flatData[i];
                index += 2;
                count = 1;
            }
            //adds run length to first index of encoded array and the value of the run to the second index as well as resets run counter
            if(count == 15){
                encoded[index] = (byte)count;
                encoded[index + 1] = flatData[i];
                index += 2;
                count = 0;
            }
            //If run exceeds 15 value adds 15 to first index of encoded array and the value of the run to the second index as well as resets run counter
        }
        encoded[index] = (byte)count;
        encoded[index + 1] = flatData[flatData.length - 1];
        return encoded;
    }
    //encodes flatdata array into an rledata array

    public static int getDecodedLength(byte[] rleData){
        int size = 0;
        for(int i = 0; i < rleData.length - 1;i++){
            if(i%2 == 0){
                size += rleData[i];
            }
        }
        //runs through even indexes of array to get length of runs to calculate size
        return size;
    }
    //returns size of flatdata array based off a rledata array

    public static byte[] decodeRle(byte[] rleData){
        byte[] decoded = new byte[getDecodedLength(rleData)];//new array created based on returned length of getDecodedLength Method
        int place = 0;
        for(int i = 0; i < rleData.length; i++){
            if(i%2 == 0){
                for(int j = place; j < rleData[i] + place; j++) {
                    decoded[j] = rleData[i + 1];
                }
                place += rleData[i];
            }
        }
        //runs through rledata array and adds values to new array by adding rleData[i] values of rleData[i+1] when i%2=0
        return decoded;
    }
    //returns flatdata array based on rledata array

    public static byte[] stringToData(String dataString){
        byte[] data = new byte[dataString.length()];//creates a new array same size as string parameter
        for(int i = 0; i < data.length; i++){
            int num = Integer.parseInt(dataString.substring(i,i+1),16);
            data[i] = (byte)num;
        }
        //runs to string characters changing all characters to decimal and adding it to byte array
        return data;
    }
    //returns byte rray with every index being the decimal form of the String characters

    public static String toRleString(byte[] rleData){
        String rleString = "";//creates new string
        for(int i = 0; i < rleData.length; i++){
            if((i)%2 == 0){
                rleString += Byte.toString(rleData[i]);
            }
            //converts value of byte array to string and concats it to new rlestring when i%2 = 0
            else{
                int hex = (int)rleData[i];
                rleString += Integer.toHexString(hex);
                if (i != rleData.length - 1) {
                    rleString += ":";
                }
            }
            //converts value of byte array to string and concats it to new rlestring and concats delimiters when i%2 != 0 unless it is last index in array
        }
        return rleString;
    }
    //returns rlestring with delimiters

    public static byte[] stringToRle(String rleString){
        String[] str = rleString.split(":");//creates new string array removing delimiters
        byte[] rleData = new byte[2*str.length];//creates new byte array twice the length of string array
        int index = 0;
        for(int i = 0; i < str.length; i++){
            if(str[i].length() == 2){
                rleData[index] = Byte.parseByte(str[i].substring(0,1));
                int hex = Integer.parseInt(str[i].substring(1,2),16);
                rleData[index + 1] = (byte)hex;
                index += 2;
            }
            //Checks to see if index of string array is 2 charcters and then adds first character as a byte to curent index of the loop to byte array and adds decimal value of second character to next index of byte array
            else{
                rleData[index] = Byte.parseByte(str[i].substring(0,2));
                int hex = Integer.parseInt(str[i].substring(2,3),16);
                rleData[index + 1] = (byte)hex;
                index += 2;
            }
            //if index of string array is 3 charcters then the first 2 character are added as a byte to curent index of the loop to byte array and adds decimal value of the third character to next index of byte array
        }
        return rleData;
    }
    //returns rleData array based off an rleString parameter

    public static void main(String args[]){
        Scanner input = new Scanner(System.in);
        byte[] flatData = {};
        byte[] rleData = {};
        String rleString = "";
        String rleHex = "";
        String flatHex = "";
        //variables created to hold values
        System.out.println("Welcome to the RLE image encoder!");
        System.out.println("\nDisplaying Spectrum Image:");
        //displays welcome message
        ConsoleGfx.displayImage(ConsoleGfx.testRainbow);
        while(true){//allows program to continue without restarting
            System.out.println("\n\nRLE Menu\n--------\n0. Exit\n1. Load File\n2. Load Test Image\n3. Read RLE String\n4. Read RLE Hex String\n5. Read Data Hex String\n6. Display Image\n7. Display RLE String\n8. Display Hex RLE Data\n9. Display Hex Flat Data\n\nSelect a Menu Option:");
            //displays menu
            int option = input.nextInt();
            if(option == 0){
                break;
            }
            //ends program
            else if(option == 1){
                System.out.println("Enter name of file to load:");
                String file = input.next();
                flatData = ConsoleGfx.loadFile(file);
                rleData =  encodeRle(flatData);
            }
            //loads a filedata to rleData and flatData
            else if(option == 2){
                System.out.println("Test image data loaded.");
                flatData = ConsoleGfx.testImage;
                rleData =  encodeRle(flatData);
            }
            //loads the test images data to flatData and rleData
            else if(option == 3){
                System.out.println("Enter an RLE string to be decoded:");
                rleString = input.next();
                rleData = stringToRle(rleString);
                flatData = decodeRle(rleData);
            }
            //uses user input of rleString to load rleData and flatData
            else if(option == 4){
                System.out.println("Enter the hex string holding RLE data:");
                rleHex = input.next();
                rleData = stringToData(rleHex);
                flatData = decodeRle(rleData);
            }
            //uses user input of hexString to load rleData and flatData
            else if(option == 5){
                System.out.println("Enter the hex string holding flat data:");
                flatHex = input.next();
                flatData = stringToData(flatHex);
                rleData = encodeRle(flatData);
            }
            //uses user input of hexString to load rleData and flatData
            else if(option == 6){
                System.out.println("Displaying image...");
                ConsoleGfx.displayImage(flatData);
            }
            //displays image of current loaded data
            else if(option == 7){
                System.out.println("RLE representation:" + toRleString(rleData));
            }
            //displays rleString of current loaded data
            else if(option == 8){
                System.out.println("RLE hex values:" + toHexString(rleData));
            }
            //displays rle hexString of current loaded data
            else if(option == 9){
                System.out.println("Flat hex values:" + toHexString(flatData));
            }
            //displays raw hexString of current loaded data
        }
    }
}