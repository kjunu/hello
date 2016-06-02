# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  
  config.vm.box = "bento/centos-7.1"
  (1..2).each do |i|
    config.vm.define vm_name = "server-#{i}" do |config|
      config.cache.scope = :box
      config.vm.hostname = vm_name
      file_to_disk = "./tmp/server_disk-#{i}.vdi"
      config.vm.provider "virtualbox" do | v |
        unless File.exist?(file_to_disk)
          v.customize ['createhd', '--filename', file_to_disk, '--size', 10 * 1024]
        end
        v.customize ['storageattach', :id, '--storagectl','SATA Controller', '--port', 1, '--device', 0, '--type', 'hdd', '--medium', file_to_disk]
      end
      serviceIP = "172.21.11.#{i+10}"
      storageIP = "172.21.12.#{i+10}"
      config.vm.network :private_network, ip: serviceIP 
      config.vm.network :private_network, ip: storageIP 
      #config.vm.provision "shell", path: "deploy_script/deploy_mount_disk.sh"
      #config.vm.provision "shell", path: "deploy_script/deploy_package.sh"
      #config.vm.provision "shell", path: "deploy_script/glusterdstart.sh"
    end
  end
  config.vm.define vm_name = "client" do |config|
    config.cache.scope = :box
    config.vm.hostname = vm_name
    serviceIP = "172.21.11.10"
    #storageIP = "172.21.12.10"
    config.vm.network :private_network, ip: serviceIP
    #config.vm.network :private_network, ip: storageIP
    #config.vm.provision "shell", path: "deploy_script/deploy_package.sh"
  end
  config.vm.define vm_name = "client2" do |config|
    config.cache.scope = :box
    config.vm.hostname = vm_name
    serviceIP = "172.21.11.101"
    #storageIP = "172.21.12.10"
    config.vm.network :private_network, ip: serviceIP
    #config.vm.network :private_network, ip: storageIP
    config.vm.provision "shell", path: "deploy_script/deploy_package.sh"
  end

  # config.vm.provider "virtualbox" do |vb|
  #   # Display the VirtualBox GUI when booting the machine
  #   vb.gui = true
  #
  #   # Customize the amount of memory on the VM:
  #   vb.memory = "1024"
  # end
  #
end
