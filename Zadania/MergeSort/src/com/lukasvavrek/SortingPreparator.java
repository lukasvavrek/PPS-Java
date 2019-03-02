package com.lukasvavrek;

import java.util.Random;

public class SortingPreparator {
    public float[] prepare(int length) {
        float[] arr = new float[length];
        Random rand = new Random();

        for (int i = 0; i < length; i++) {
            arr[i] = rand.nextFloat();
        }

        return arr;
    }
}
