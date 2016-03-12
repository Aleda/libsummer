/**
* @file perceptron.go
* @brief concrete a perceptron.
*		 The main formula: W_new = W_old + A * (y - output) * Xi
* @author Aleda(aledalee@foxmail.com | aleda.cn)
* @version 1.0.0
* @date 2015-11-14
* @input
5 5 0.321 100
1 2 3 4 5 0
2 3 4 5 6 1
-1 2 3 4 8 0
1 1 2 2 3 0
-5 8 8 7 7 1
0.1 0.2 0.3 0.4 0.5 0.6
* @output
...
-7.283 3.410 14.103 5.536 2.747 -12.561
-7.283 3.410 14.103 5.536 2.747 -12.561
*/

package main

import (
	//"bufio"
	"fmt"
)

const (
	MAX_SAMPLES_NUM = 1000 + 5
	MAX_FEATURE_NUM = 1000 + 5
)

// set samples_arr[i][0] = 1
func init_samples_arr(samples_arr [][MAX_FEATURE_NUM]int, samples_num int) {
	for i := 0; i < samples_num; i++ {
		samples_arr[i][0] = 1
	}
}

func sum(samples_arr [MAX_FEATURE_NUM]int, weights_arr []float32, arr_length int) float32 {
	var sum float32 = 0
	for i := 0; i <= arr_length; i++ {
		sum += float32(samples_arr[i]) * weights_arr[i]
	}
	return sum
}

func get_weight_new(samples_arr [MAX_FEATURE_NUM]int, weights_arr []float32, observation int,
	arr_length int, iterations_rate float32, output int) {
	for i := 0; i <= arr_length; i++ {
		var delta float32 = iterations_rate * float32((observation - output)) * float32(samples_arr[i])
		weights_arr[i] = weights_arr[i] + delta
	}
}

func print_weights(weights_arr []float32, arr_length int) {
	for i := 0; i < arr_length; i++ {
		fmt.Printf("%.3f ", weights_arr[i])
	}
	fmt.Printf("%.3f\n", weights_arr[arr_length])
}

func Perceptron(samples_arr [][MAX_FEATURE_NUM]int, weights_arr []float32, observations_arr []int,
	features_num int, samples_num int, iterations_num int, iterations_rate float32) bool {
	init_samples_arr(samples_arr, samples_num)
	for iterations_num > 0 {
		delta := [MAX_FEATURE_NUM]float32{0}
		for i := 0; i < samples_num; i++ {
			var output int = 0
			if sum(samples_arr[i], weights_arr, features_num) > 0 {
				output = 1
			}
			for k := 0; k <= features_num; k++ {
				delta[k] += iterations_rate * float32(observations_arr[i]-output) *
					float32(samples_arr[i][k])
			}
			// Changint in process. more quickly convergence.
			//get_weight_new(samples_arr[i], weights_arr, observations_arr[i],
			//	features_num, iterations_rate, output)
		}
		for i := 0; i <= features_num; i++ {
			weights_arr[i] += delta[i]
		}
		print_weights(weights_arr, features_num)
		iterations_num--
	}
	return true
}

func main() {
	var features_num, samples_num, iterations_num int
	var iterations_rate float32
	samples_arr := [MAX_SAMPLES_NUM][MAX_FEATURE_NUM]int{}
	weights_arr := [MAX_FEATURE_NUM]float32{}
	observations_arr := [MAX_FEATURE_NUM]int{}

	var handle_input = func() {
		fmt.Scanf("%d%d%f%d", &features_num, &samples_num, &iterations_rate, &iterations_num)
		for i := 0; i < samples_num; i++ {
			for j := 1; j <= features_num; j++ {
				fmt.Scanf("%d", &samples_arr[i][j])
			}
			fmt.Scanf("%d", &observations_arr[i])
		}
		for j := 0; j <= features_num; j++ {
			fmt.Scanf("%f", &weights_arr[j])
		}
	}
	handle_input()
	Perceptron(samples_arr[:], weights_arr[:], observations_arr[:], features_num, samples_num,
		iterations_num, iterations_rate)
}
