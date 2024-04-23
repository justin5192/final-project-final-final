// Code for creating line graph for this is based on code from following youtube videos:
// https://www.youtube.com/watch?v=g5bp02-CRAc&t=1s
// https://www.youtube.com/watch?v=Wk8pIxcidv8
// 


const margin = { top: 50, right: 50, bottom: 50, left: 50 };
const width = 400;
const height = 400;

const x = d3.scaleLinear().range([0, width]);

const y = d3.scaleLinear().range([height, 0]);

const svg = d3.select("#graph_div")
  .append("svg").attr("width", width + margin.left + margin.right).attr("height", height + margin.top + margin.bottom)
  .append("g").attr("transform", `translate(${margin.left},${margin.top})`);

// Load and parse data

input = "genetic_output.csv";


function select_genetic() {
  input = "input_data_1.csv";
  //input = "genetic_output.csv";
 // generate_graph();
}

function select_annealing() {
  input = "annealing_output.csv";
  //generate_graph();
}

function select_branch() {
  input = "branch_output.csv";
  //generate_graph();
}

function select_christofides() {
  input = "christofides_output.csv";
  //generate_graph();
}

d3.csv(input).then(function (data) {
  data.forEach(d => {
    d.x_value = +d.x_value;
    d.y_value = +d.y_value;

});

console.log(data)

// Define the x and y domains
  
x.domain([-1, d3.max(data, d => d.x_value)]);
y.domain([-1, d3.max(data, d => d.y_value)]);

// Adds x-axis
  
svg.append("g").attr("transform", `translate(0,${height})`).call(d3.axisBottom(x));
  
  
// Adds y-axis

svg.append("g").call(d3.axisLeft(y));

const line = d3.line()
    .x(d => x(d.x_value))
    .y(d => y(d.y_value));


    svg.append("path")
    .datum(data)
    .attr("fill", "none")
    .attr("stroke", "blue")
    .attr("stroke-width", 1)
    .attr("d", line);

// Graph title
  
svg.append("text") // text?
.attr("class", "graph-title")
.attr("x", margin.left - 20)
.attr("y", margin.top - 70)
.style("font-size", "15px")
.style("font-weight", "bold")
.style("font-family", "sans-serif")
.text("The best calculated path for the traveling salesperson")
})
