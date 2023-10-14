using LinearAlgebra, Distances, StatsBase, Printf



function calculation()
kk = 3 # dimension of the problem
n = 1000 # number of atoms
t = 10 # number of instances for each number of atom
r = 1.526 # atoms distance
max_dist = 500 # maximum distance between two atoms
theta = 1.91 # consecutive atom angle
omega_options = [1.0472 3.14159 5.23599] # torsional angle possibilities // 60, 180 and 300 degrees 

cos_theta = cos(theta)
sin_theta = sin(theta)
for k=1:t
final_matrix = [0
		0
		0
		1]
B = zeros(n,4,4)

B[1,:,:] = Diagonal(ones(4,4))
println("cheguei aqui")
B[2,:,:] = [-1 0 0 r
	0 1 0 0
 	0 0 -1 0
	0 0 0  1]
println("cheguei aqui")
B[3,:,:] = [-cos_theta -sin_theta 0 -r*cos_theta
	sin_theta -cos_theta 0	r*sin_theta
	0	0	1	0
	0	0	0	1]

omega = [0 0 0]
#B_current = B[1,:,:]*B[2,:,:]*B[3,:,:]
B_current = Diagonal(ones(4,4))
println("cheguei aqui")
x = zeros(n,3)
j=1


for i=1:n
omega = [omega omega_options[rand(1:length(omega_options))]]
cos_omega = cos(omega[i])
sin_omega = sin(omega[i])
	if i > 3
		B[i,:,:] = [-cos_theta -sin_theta 0 -r*cos_theta
				sin_theta*cos_omega -cos_theta*cos_omega -sin_omega r*sin_theta*cos_omega
			sin_theta*sin_omega -cos_theta*sin_omega cos_omega r*sin_theta*sin_omega
			0	0	0	1]
	end

### update the multiplication matrix B1..Bn
B_current = B_current*B[i,:,:]


#### calculate the cartesian coordenates of atom i

solution = B_current*final_matrix
x[i,:] = solution[1:kk]

end

distance_matrix = zeros(n,n)
for i = 1:n
	for j=i:n
		distance_matrix[i,j] = round(euclidean(x[i,:],x[j,:]),digits=5)
	end
end

distance_list  = reshape(distance_matrix, 1, length(distance_matrix))

distance_list_aux = unique(distance_list)

histogram = zeros(length(distance_list_aux),2)

mkpath(@sprintf("Instance_%d",n))
print_list = open(@sprintf("Instance_%d/distance_frequency_size%d_instance%d.dat",n,n,k),"w")
#print_list = open(@sprintf("Instance_%d/distance_frequency_size%d_instance%d_max_distance_%d.dat",n,n,k,max_dist),"w")
print_list2 = open(@sprintf("Instance_%d/position_size%d_instance%d_max_distance_%d.dat",n,n,k,max_dist),"w")

for i=1:n
print(print_list2, x[i,1], "\t", x[i,2],"\t ", x[i,3])
println(print_list2)
end


println(print_list)
b = 1
for i=1:length(distance_list_aux)
	if distance_list_aux[i] > 0 && distance_list_aux[i] <= max_dist
		a = findall(x -> x == distance_list_aux[i], distance_list)
		histogram[i,:] = [distance_list_aux[i] length(a)]
		print(print_list, " ", histogram[i,2], " ", histogram[i,1])
		println(print_list)
		b = b +1
	end
end




#println(print_list, "param m :=", b-1 ,";")
#println(print_list, "param l :=", n ,";")
#println(print_list, "end;")



close(print_list)
close(print_list2)

end
return 
end
