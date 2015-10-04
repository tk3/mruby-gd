MRuby::Gem::Specification.new('mruby-gd') do |spec|
  spec.license = 'MIT'
  spec.author  = 'qtakamitsu'
  spec.summary = 'GD Graphics Library for mruby'
  spec.linker.library_paths << `gdlib-config --libdir`.chomp
  spec.linker.libraries << 'gd'
end
