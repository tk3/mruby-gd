MRuby::Gem::Specification.new('GD') do |spec|
  spec.license = 'MIT'
  spec.author  = 'qtakamitsu'
  spec.linker.library_paths << `gdlib-config --libdir`.chomp
  spec.linker.libraries << 'gd'
end
