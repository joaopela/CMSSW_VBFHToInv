
iEvent.getByLabel("puJetMva","fullDiscriminant", puJetIdMVA);
edm::Handle<edm::ValueMap<float> > puJetIdMVA;

jet.set_pu_id_mva_value((*puJetIdMVA)[jetCollectionView->refAt(iJ)->originalObjectRef()]);