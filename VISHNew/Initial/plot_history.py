import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib import axes,colors
from matplotlib.font_manager import FontProperties
plot_object="ed"
ed=np.fromfile("/home/qinjian/research/simulation/UrqmdVishnu/VISHNew/Initial/{}_history.dat".format("ed"),dtype="float64")
time=12.46
dt=0.02
x = np.arange(-13, 13.1, 0.1)
y = np.arange(-13, 13.1, 0.1)
X, Y = np.meshgrid(x, y)
x_lattice=261
y_lattice=261
t_lattice=int(ed.size/(x_lattice*y_lattice))
ed=ed.reshape(int(t_lattice),x_lattice,y_lattice)
u1=np.fromfile("/home/qinjian/research/simulation/UrqmdVishnu/VISHNew/Initial/{}_history.dat".format("u1"),dtype="float64").reshape(int(t_lattice),x_lattice,y_lattice)
u2=np.fromfile("/home/qinjian/research/simulation/UrqmdVishnu/VISHNew/Initial/{}_history.dat".format("u2"),dtype="float64").reshape(int(t_lattice),x_lattice,y_lattice)
divide=80
print(u1.shape,u2.shape,ed.shape)
ed_plot_x=ed[0:t_lattice:divide,:,int(y_lattice/2)]
u1_plot_x=u1[0:t_lattice:divide,:,int(y_lattice/2)]
u2_plot_x=u2[0:t_lattice:divide,:,int(y_lattice/2)]
ed_plot_y=ed[0:t_lattice:divide,int(y_lattice/2),:]
u1_plot_y=u1[0:t_lattice:divide,int(y_lattice/2),:]
u2_plot_y=u2[0:t_lattice:divide,int(y_lattice/2),:]


for i in range(0,int(t_lattice/divide)+1):
  p1=plt.plot(x,ed_plot_x[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("x")
plt.ylabel("ed")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(x,u1_plot_x[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("x")
plt.ylabel("u1")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(x,u1_plot_x[i,:]/ed_plot_x[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("x")
plt.ylabel("u1/ed")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(x,u2_plot_x[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("x")
plt.ylabel("u2")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(x,u2_plot_x[i,:]/ed_plot_x[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("x")
plt.ylabel("u2/ed")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(y,ed_plot_y[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("y")
plt.ylabel("ed")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(y,u1_plot_y[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("y")
plt.ylabel("u1")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(y,u1_plot_y[i,:]/ed_plot_y[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("y")
plt.ylabel("u1/ed")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(y,u2_plot_y[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("y")
plt.ylabel("u2")
plt.legend( prop = {'size':8})
plt.show()

for i in range(0,int(t_lattice/divide)+1):
  plt.plot(y,u2_plot_y[i,:]/ed_plot_y[i,:],label="t={:.2f}".format(dt*divide*i))
plt.xlabel("y")
plt.ylabel("u2/ed")
plt.legend( prop = {'size':8})
plt.show()