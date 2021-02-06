
import java.util.Locale;
import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        try{
            Scanner in = new Scanner(System.in);
            String command = in.next().toLowerCase(Locale.ROOT);
            String inputFileName = in.next();

            Parser parser = new Parser();
            Alphabet alphabet = new Alphabet("src/resources/alphabet.txt"); // TODO: find correct path

            if(command.equals("decode")){
                MorseDecoder decoder = new MorseDecoder(alphabet);
                String outputFileName = "decode_result.txt";
                decoder.decode(parser.parseForDecoder(inputFileName), outputFileName);
                System.out.println("Decode completed. Output file: " + outputFileName);
            }
            else if(command.equals("code")){
                String outputFileName = "encode_result.txt";
                MorseEncoder encoder = new MorseEncoder(alphabet);
                encoder.encode(parser.parseForEncoder(inputFileName), outputFileName);
                System.out.println("Encode completed. Output file: " + outputFileName);
            }

        }
        catch(Throwable e){
            System.err.println("Error somewhere in program: " + e.getLocalizedMessage());
        }
    }
}
