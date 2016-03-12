/**
* @file naive_bayesian.go
* @brief
* @author Aleda(aledalee@foxmail.com | aleda.cn)
* @version 1.0.0
* @date 2015-12-12
* @input:
3 10 3 4
2 1 1 0
2 0 1 1
1 1 1 0
0 0 1 0
0 0 1 2
0 1 0 0
1 0 0 1
1 0 1 3
1 1 1 0
2 0 0 1
1 0 1
2 1 1
1 1 1
* @output:
0.000000 0.033333 0.000000 0.100000 3
0.060000 0.000000 0.000000 0.000000 0
0.120000 0.000000 0.000000 0.000000 0
*/

package main

import (
	"fmt"
)

const (
	MAX_CLASS_NUM    = 32 + 2
	MAX_ACTIVITY_NUM = 8 + 2
	MAX_FEATURES_NUM = 100 + 2
)

type Bayesianer interface {
	Build(samplesSlice [][]int, markSlice []int) int
	Test(featuresSlice []int, chanceSlice []float64) int
}

type Bayesian struct {
	Bayesianer
	chanceSlice         [MAX_FEATURES_NUM][MAX_CLASS_NUM][MAX_ACTIVITY_NUM]float64
	activityChanceSlice [MAX_ACTIVITY_NUM]float64
}

func (bys *Bayesian) Build(samplesSlice [][]int, markSlice []int) int {
	if len(samplesSlice) <= 0 {
		return 0
	}
	samplesNum := len(samplesSlice)
	var featuresNum int = 0
	if featuresNum = len(samplesSlice[0]); featuresNum <= 0 {
		return 0
	}
	countActivityArr := [MAX_FEATURES_NUM][MAX_CLASS_NUM][MAX_ACTIVITY_NUM]int{}
	countClassArr := [MAX_FEATURES_NUM][MAX_CLASS_NUM]int{}
	countArr := [MAX_ACTIVITY_NUM]int{}
	handle_count := func() {
		for j := 0; j < featuresNum; j++ {
			for i := range samplesSlice {
				countActivityArr[j][samplesSlice[i][j]][markSlice[i]]++
				countClassArr[j][samplesSlice[i][j]]++
			}
		}
		for i := range samplesSlice {
			countArr[markSlice[i]]++
		}
	}
	handle_count()
	for i := 0; i < featuresNum; i++ {
		for j := 0; j < MAX_CLASS_NUM; j++ {
			for k := 0; k < MAX_ACTIVITY_NUM; k++ {
				if countArr[k] == 0 {
					continue
				}
				bys.chanceSlice[i][j][k] = float64(countActivityArr[i][j][k]) /
					float64(countArr[k])
			}
		}
	}
	for i := 0; i < MAX_ACTIVITY_NUM; i++ {
		if countArr[i] != 0 {
			bys.activityChanceSlice[i] = float64(countArr[i]) / float64(samplesNum)
		}
	}
	return 1
}

func (bys *Bayesian) Test(featuresSlice []int, chanceSlice []float64, c int) int {
	for i := 0; i < c; i++ {
		probilityAns := 1.0
		for j, v := range featuresSlice {
			probilityAns *= bys.chanceSlice[j][v][i]
		}
		chanceSlice[i] = probilityAns * bys.activityChanceSlice[i]
	}
	bestActivity := -1
	maxChance := -1.0
	for i, v := range chanceSlice {
		if maxChance < v {
			maxChance = v
			bestActivity = i
		}
	}
	return bestActivity
}

func main() {
	var featuresNum, samplesNum, testNum, c int
	var samplesSlice, testSlice [][]int
	var markSlice []int
	handle_input := func() {
		fmt.Scanf("%d%d%d%d", &featuresNum, &samplesNum, &testNum, &c)
		samplesSlice = make([][]int, samplesNum, samplesNum+5)
		testSlice = make([][]int, testNum, testNum+5)
		markSlice = make([]int, samplesNum, samplesNum+5)
		for i := 0; i < samplesNum; i++ {
			samplesSlice[i] = make([]int, featuresNum, featuresNum+5)
			for j := 0; j < featuresNum; j++ {
				fmt.Scanf("%d", &samplesSlice[i][j])
			}
			fmt.Scanf("%d", &markSlice[i])
		}
		for i := 0; i < testNum; i++ {
			testSlice[i] = make([]int, featuresNum, featuresNum+5)
			for j := 0; j < featuresNum; j++ {
				fmt.Scanf("%d", &testSlice[i][j])
			}
		}
	}
	handle_output := func(chanceSlice []float64, activity int) {
		for _, v := range chanceSlice {
			fmt.Printf("%.6f ", v)
		}
		fmt.Printf("%d\n", activity)
	}
	handle_input()
	bayesian := Bayesian{chanceSlice: [MAX_FEATURES_NUM][MAX_CLASS_NUM][MAX_ACTIVITY_NUM]float64{},
		activityChanceSlice: [MAX_ACTIVITY_NUM]float64{}}
	bayesian.Build(samplesSlice, markSlice)
	handle_test := func() {
		var activity int
		for i := 0; i < testNum; i++ {
			ansSlice := make([]float64, c)
			activity = bayesian.Test(testSlice[i], ansSlice, c)
			handle_output(ansSlice, activity)
		}
	}
	handle_test()
}
