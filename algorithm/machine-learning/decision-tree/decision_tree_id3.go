/**
* @file decision_tree_id3.go
* @brief Simple inplementation of ID3
* @author Aleda(aledalee@foxmail.com | aleda.cn)
* @version 1.0.0
* @date 2015-11-28
* @input
3 10
2 1 1 0
2 0 1 1
1 1 1 0
0 1 0 0
0 0 1 2
0 1 0 0
1 0 0 1
1 0 1 3
1 1 1 0
2 0 0 1
* @output
inner(1)
---0->inner(0)
------0->leaf(2)
------1->inner(2)
---------0->leaf(1)
---------1->leaf(3)
------2->leaf(1)
---1->leaf(0)
*/
package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
)

const (
	MAX_FEATURES_NUM = 100 + 5
	MAX_SAMPLES_NUM  = 1000 + 5
	MAX_ACTIVITY_NUM = 8 + 2
	MAX_CLASS_NUM    = 32 + 2
)

type DecisionTreeNode struct {
	featureId int
	nodeType  int // 0 => DecisionNode; 1 => EndNode
	childs    []*DecisionTreeNode
}

type DecisionTreer interface {
	FindBestFeature([][]int, []int, []int, *[]int, *int) int
	BuildTree([][]int, []int, []int) *DecisionTreeNode
	IsEndNode([]int, []int) (bool, int)
	GetSubSampleData([][]int, []int, int, int, [][]int, []int) bool
	PrintTree()
}

type DecisionTree struct {
	DecisionTreer
	root *DecisionTreeNode
}

func (dt *DecisionTree) IsEndNode(markArr []int, classArr []int) (bool, int) {
	if len(markArr) == 0 || len(classArr) == 0 {
		return true, -1
	}
	oldActivity := markArr[0]
	for i := 1; i < len(markArr); i++ {
		if oldActivity != markArr[i] {
			return false, -1
		}
	}
	return true, oldActivity
}

func ComputeEntropy(p float64) float64 {
	if p == 0 {
		return 0
	}
	return -p * (math.Log2(p))
}

func CalEntropy(inputMap map[int]int) float64 {
	sum := 0.0
	allNum := 0
	for _, num := range inputMap {
		allNum += num
	}
	for _, num := range inputMap {
		p := float64(num) / float64(allNum)
		sum += ComputeEntropy(p)
	}
	return sum
}

func (dt *DecisionTree) FindBestFeature(samplesArr [][]int,
	markArr []int, featureArrIndex []int, bestLeftArrIndex *[]int, bestFeatureId *int) int {
	samplesNum := len(markArr)
	classNumArr := make([]int, MAX_CLASS_NUM)
	activityNumArr := make([]map[int]int, MAX_CLASS_NUM)
	minEntropy := math.MaxFloat64
	clearClassNumArrfunc := func() {
		for i := 0; i < len(classNumArr); i++ {
			classNumArr[i] = 0
		}
	}
	clearActivityNumArrfunc := func() {
		for i := 0; i < MAX_CLASS_NUM; i++ {
			activityNumArr[i] = nil
			activityNumArr[i] = make(map[int]int, MAX_ACTIVITY_NUM)
		}
	}
	for i := 0; i < len(featureArrIndex); i++ {
		origIndex := featureArrIndex[i]
		clearClassNumArrfunc()
		clearActivityNumArrfunc()
		for j := 0; j < samplesNum; j++ {
			classNumArr[samplesArr[j][i]]++
			activityNumArr[samplesArr[j][i]][markArr[j]]++
		}
		bufio.NewReader(os.Stdin).ReadBytes('\n')
		var sumEntropy float64 = 0.0
		for classId, classNum := range classNumArr {
			if classNum == 0 {
				continue
			}
			classIdChance := float64(classNum) / float64(samplesNum)
			activityChance := CalEntropy(activityNumArr[classId])
			sumEntropy += classIdChance * activityChance
		}
		if sumEntropy < minEntropy {
			minEntropy = sumEntropy
			*bestFeatureId = origIndex
		}
	}
	for _, classId := range featureArrIndex {
		if classId == *bestFeatureId {
			continue
		}
		*bestLeftArrIndex = append(*bestLeftArrIndex, classId)
	}
	return 1
}

func (dt *DecisionTree) GetSubSampleData(samplesArr [][]int, markArr []int, featureId int,
	classId int, subSamplesArr *[][]int, subMarkArr *[]int) bool {
	lineNum := 0
	for i := 0; i < len(samplesArr); i++ {
		if samplesArr[i][featureId] != classId {
			continue
		}
		*subSamplesArr = append(*subSamplesArr, make([]int, 0, MAX_FEATURES_NUM))
		(*subMarkArr) = append((*subMarkArr), markArr[i])
		for j := 0; j < len(samplesArr[i]); j++ {
			if j == featureId {
				continue
			}
			(*subSamplesArr)[lineNum] = append((*subSamplesArr)[lineNum], samplesArr[i][j])
		}
		lineNum++
	}
	return true
}

func (dt *DecisionTree) BuildTree(samplesArr [][]int, markArr []int, featureArrIndex []int) *DecisionTreeNode {
	//samplesNum := len(markArr)
	//featuresNum := len(samplesArr[0])
	node := DecisionTreeNode{-1, 0, make([]*DecisionTreeNode, 0, int(MAX_CLASS_NUM/2))}
	if isEndNode, activityNum := dt.IsEndNode(markArr, featureArrIndex); isEndNode {
		node.nodeType = 1
		node.featureId = activityNum
		return &node
	}
	bestFeatureId := -1
	bestLeftArrIndex := make([]int, 0, MAX_FEATURES_NUM)
	dt.FindBestFeature(samplesArr, markArr, featureArrIndex, &bestLeftArrIndex, &bestFeatureId)
	node.featureId = bestFeatureId
	indexId := func() int {
		for i, v := range featureArrIndex {
			if v == bestFeatureId {
				return i
			}
		}
		return -1
	}()
	for classId := range bestLeftArrIndex {
		subSamplesArr := make([][]int, 0, MAX_SAMPLES_NUM)
		subMarkArr := make([]int, 0, MAX_SAMPLES_NUM)
		dt.GetSubSampleData(samplesArr, markArr, indexId, classId,
			&subSamplesArr, &subMarkArr)
		node.childs = append(node.childs, dt.BuildTree(subSamplesArr, subMarkArr, bestLeftArrIndex))
	}
	return &node
}

func (dt *DecisionTree) PrintTree(p *DecisionTreeNode) {
	if p == nil || p.featureId == -1 {
		return
	}
	if p.nodeType == 1 {
		fmt.Printf("EndNode, Its activityNum: %d\n", p.featureId)
		return
	}
	fmt.Printf("FatherNode, featureId: %d\n", p.featureId)
	for i, child := range p.childs {
		fmt.Println("father: ", p.featureId, "\tchildId: ", i)
		dt.PrintTree(child)
	}
}

func main() {
	var featuresNum, samplesNum int
	//var samplesArr [MAX_SAMPLES_NUM][MAX_FEATURES_NUM]int
	var samplesArr [][]int
	//var markArr [MAX_SAMPLES_NUM]int
	var markArr []int
	var featureArrIndex []int
	handle_input := func() {
		fmt.Scanf("%d%d", &featuresNum, &samplesNum)
		samplesArr = make([][]int, samplesNum, samplesNum+5)
		markArr = make([]int, samplesNum, samplesNum+5)
		featureArrIndex = make([]int, featuresNum)
		for j := 0; j < featuresNum; j++ {
			featureArrIndex[j] = j
		}
		for i := 0; i < samplesNum; i++ {
			samplesArr[i] = make([]int, featuresNum, featuresNum+5)
			for j := 0; j < featuresNum; j++ {
				fmt.Scanf("%d", &samplesArr[i][j])
			}
			fmt.Scanf("%d", &markArr[i])
		}
	}
	handle_input()
	decisionTree := DecisionTree{
		root: &DecisionTreeNode{-1, 0, make([]*DecisionTreeNode, 0, MAX_FEATURES_NUM)},
	}
	decisionTree.root = decisionTree.BuildTree(samplesArr, markArr, featureArrIndex)
	decisionTree.PrintTree(decisionTree.root)
}
