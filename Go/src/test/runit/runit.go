package main

import (
    "io"
    "os"
    "unicode/utf8"
    "fmt"
    "strconv"
    "time"
)

func main() {
    ts := time.Now()
    f, err := os.Open("./temp.txt")

    if err != nil {
        panic(err)
    }

    defer f.Close()

    keepGoing := true
    for keepGoing != false {
        cNum, len := readNumbers(f)
        if len < 16 {
            keepGoing = false
        } else {
            processNumber(cNum)
        }
    }
    te := time.Now()
    tt := te.Sub(ts)
    fmt.Printf("%v\n", tt)
}

func processNumber(cardNum [16]int) {

    odd_accumulator := 0;
    even_accumulator := 0;

    for i := 0; i < 16; i++ {
        // Odd/Even processing appears reversed because of 0 based index
        if (i%2 == 0) {
            odd_accumulator += cardNum[i];
        } else {
            even_num := cardNum[i] * 2;

            if (even_num > 9) {
                even_num -= 10;
            }

            even_accumulator += even_num;
        }
    }

    if ((odd_accumulator + even_accumulator)%10 > 0) {
        fmt.Printf("FAILURE\n")
    } else {
        fmt.Printf("SUCCESS\n")
    }
}

func readNumbers(f *os.File) ([16]int, int) {

    var cardNum [16]int
    err := error(nil)
    counter := 0


    for {
        readByte := make([]byte, 1)
        _, err = f.Read(readByte)

        readChar, _ := utf8.DecodeRune(readByte)
        str := string(readChar)

        if err == io.EOF {
            return cardNum, counter
        } else if readChar == '\n' {
            return cardNum, counter
        } else if counter > 16  {
            for err != io.EOF && readChar != '\n' {
                _, err = f.Read(readByte)
            }
            return cardNum, counter
        } else {
            intVal , _ := strconv.Atoi(str)
            cardNum[15 - counter] = intVal
        }
        counter += 1
    }
}
